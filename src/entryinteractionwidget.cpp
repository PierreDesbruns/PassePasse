// Copyright (C) 2025 Pierre Desbruns
// SPDX-License-Identifier: LGPL-3.0-only

#include "entryinteractionwidget.h"

namespace pwm {

EntryInteractionWidget::EntryInteractionWidget(EntryManager* entryManager, QWidget* parent)
    : QWidget{parent}, entryManager(entryManager), m_displayMode(NoEntry)
{
    // Clipboard
    clipboard = QApplication::clipboard();

    // Labels
    displayModeLabel = new QLabel();
    entrynameLabel = new QLabel(QString(tr("Nom de l'entrée")));
    usernameLabel = new QLabel(QString(tr("Nom d'utilisateur")));
    passwordLabel = new QLabel(QString(tr("Mot de passe")));

    // Buttons
    confirmButton = new QPushButton(QString(tr("Valider")));
    cancelButton = new QPushButton(QString(tr("Annuler")));

    // Line edits
    entrynameLine = new QLineEdit();
    usernameLine = new QLineEdit();
    passwordLine = new QLineEdit();
    passwordLine->setReadOnly(true);

    // Line edit actions
    editEntrynameAction = entrynameLine->addAction(QIcon(":/edit2"), QLineEdit::TrailingPosition);
    editUsernameAction = usernameLine->addAction(QIcon(":/edit2"), QLineEdit::TrailingPosition);
    copyUsernameAction = usernameLine->addAction(QIcon(":/copy"), QLineEdit::TrailingPosition);
    editPasswordAction = passwordLine->addAction(QIcon(":/edit2"), QLineEdit::TrailingPosition);
    copyPasswordAction = passwordLine->addAction(QIcon(":/copy"), QLineEdit::TrailingPosition);
    seePasswordAction = passwordLine->addAction(QIcon(":/see"), QLineEdit::TrailingPosition);

    // Password slider
    pwdLengthSlider = new PasswordLengthSlider(60);

    // Characters checkboxes
    charTypesWidget = new CharacterTypesWidget();

    // Layout
    mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(displayModeLabel);
    mainLayout->addWidget(entrynameLabel);
    mainLayout->addWidget(entrynameLine);
    mainLayout->addWidget(usernameLabel);
    mainLayout->addWidget(usernameLine);
    mainLayout->addWidget(passwordLabel);
    mainLayout->addWidget(passwordLine);
    mainLayout->addWidget(pwdLengthSlider);
    mainLayout->addWidget(charTypesWidget);
    mainLayout->addWidget(cancelButton);
    mainLayout->addWidget(confirmButton);

    // Initializations
    updateDisplay(m_displayMode);

    // Slots / signals
    connect(this, SIGNAL(displayModeChanged(DisplayMode)), this, SLOT(updateDisplay(DisplayMode)));
    connect(seePasswordAction, SIGNAL(triggered(bool)), this, SLOT(reversePasswordEchoMode()));
    connect(copyUsernameAction, SIGNAL(triggered(bool)), this, SLOT(usernameToClipboard()));
    connect(copyPasswordAction, SIGNAL(triggered(bool)), this, SLOT(passwordToClipboard()));
    connect(editEntrynameAction, SIGNAL(triggered(bool)), this, SLOT(triggerEditEntrynameMode()));
    connect(editUsernameAction, SIGNAL(triggered(bool)), this, SLOT(triggerEditUsernameMode()));
    connect(editPasswordAction, SIGNAL(triggered(bool)), this, SLOT(triggerEditPasswordMode()));
    connect(confirmButton, SIGNAL(pressed()), this, SLOT(confirm()));
    connect(cancelButton, SIGNAL(pressed()), this, SLOT(cancel()));
}

void EntryInteractionWidget::triggerAddEntryMode()
{
    if (m_displayMode != EntryInfo)
        return;

    setDisplayMode(AddEntry);
}

void EntryInteractionWidget::triggerEditEntrynameMode()
{
    if (m_displayMode == EditEntryname)
    {
        confirm();
        entrynameLine->setPlaceholderText("");
    }
    else
    {
        if (m_displayMode != EntryInfo)
            return;
        if (entrynameLine->text().isEmpty())
            return;

        entrynameLine->setPlaceholderText(entrynameLine->text());
        setDisplayMode(EditEntryname);
    }
}

void EntryInteractionWidget::triggerEditUsernameMode()
{
    if (m_displayMode == EditUsername)
    {
        confirm();
        usernameLine->setPlaceholderText("");
    }
    else
    {
        if (m_displayMode != EntryInfo)
            return;
        if (usernameLine->text().isEmpty())
            return;

        usernameLine->setPlaceholderText(usernameLine->text());
        setDisplayMode(EditUsername);
    }
}

void EntryInteractionWidget::triggerEditPasswordMode()
{
    if (m_displayMode != EntryInfo)
        return;
    if (passwordLine->text().isEmpty())
        return;

    setDisplayMode(EditPassword);
}

void EntryInteractionWidget::triggerDeleteEntryMode()
{
    if (m_displayMode != EntryInfo)
        return;
    if (entrynameLine->text().isEmpty())
        return;

    setDisplayMode(DeleteEntry);
}

void EntryInteractionWidget::displayEntry(const Entry& entry)
{
    setDisplayMode(EntryInfo);
    entrynameLine->setText(entry.entryname());
    usernameLine->setText(entry.username());
    passwordLine->setText(entry.password());
    passwordLine->setEchoMode(QLineEdit::Password);
}

void EntryInteractionWidget::cancel()
{
    switch (m_displayMode)
    {
    case AddEntry:
        setDisplayMode(NoEntry);
        break;

    case DeleteEntry:
        setDisplayMode(EntryInfo);
        break;

    case EditPassword:
        setDisplayMode(EntryInfo);
        break;

    default:
        break;
    }
}

void EntryInteractionWidget::confirm()
{
    // Getting values from widgets
    QString entryname = entrynameLine->text();
    QString username = usernameLine->text();
    int passwordLength = pwdLengthSlider->value();
    int characterTypes = charTypesWidget->checkedBoxes();

    // Requesting entry manager after verifications
    switch (m_displayMode)
    {
    case AddEntry:
        if (entryname.isEmpty())
        {
            qWarning() << "EntryInteractionWidget: Entry name is empty. Did not emit add signal.";
            return;
        }
        if (username.isEmpty())
        {
            qWarning() << "EntryInteractionWidget: User name is empty. Did not emit add signal.";
            return;
        }
        if (passwordLength < 1)
        {
            qWarning() << "EntryInteractionWidget: Pasword length is too small. Did not emit add signal.";
            return;
        }
        if (!characterTypes)
        {
            qWarning() << "EntryInteractionWidget: No characters selected. Did not emit add signal.";
            return;
        }
        emit addEntryConfirmed(Entry(entryname, username, passwordLength, characterTypes));
        // Resetting display
        setDisplayMode(EntryInfo);
        break;

    case EditEntryname:
        emit editEntrynameConfirmed(Entry(entryname, username), Entry(entrynameLine->placeholderText(), username));
        // Resetting display
        setDisplayMode(EntryInfo);
        break;

    case EditUsername:
        emit editUsernameConfirmed(Entry(entryname, username), Entry(entryname, usernameLine->placeholderText()));
        // Resetting display
        setDisplayMode(EntryInfo);
        break;

    case EditPassword:
        if (passwordLength < 1)
        {
            qWarning() << "EntryInteractionWidget: Pasword length is too small. Did not emit reset signal.";
            return;
        }
        if (!characterTypes)
        {
            qWarning() << "EntryInteractionWidget: No characters selected. Did not emit reset signal.";
            return;
        }
        emit editPasswordConfirmed(Entry(entryname, username, passwordLength, characterTypes));
        // Resetting display
        setDisplayMode(EntryInfo);
        break;

    case DeleteEntry:
        emit deleteEntryConfirmed(Entry(entryname, username));
        entrynameLine->clear();
        usernameLine->clear();
        passwordLine->clear();
        // Resetting display
        setDisplayMode(NoEntry);
        break;

    default: break;
    }
}

void EntryInteractionWidget::updateDisplay(DisplayMode displayMode)
{
    switch (displayMode)
    {
    case NoEntry:
        displayModeLabel->setText(QString(tr("AUCUNE ENTREE SELECTIONNEE")));
        // Lines
        entrynameLine->setReadOnly(true);
        usernameLine->setReadOnly(true);
        passwordLine->setEchoMode(QLineEdit::Password);
        // Hidden widgets
        pwdLengthSlider->hide();
        charTypesWidget->hide();
        cancelButton->hide();
        confirmButton->hide();
        // Enabled actions
        editEntrynameAction->setEnabled(false);
        editUsernameAction->setEnabled(false);
        editPasswordAction->setEnabled(false);
        copyUsernameAction->setEnabled(false);
        copyPasswordAction->setEnabled(false);
        seePasswordAction->setEnabled(false);
        break;

    case EntryInfo:
        displayModeLabel->setText(QString(tr("INFORMATION SUR L'ENTREE")));
        // Lines
        entrynameLine->setReadOnly(true);
        usernameLine->setReadOnly(true);
        passwordLine->setEchoMode(QLineEdit::Password);
        // Hidden widgets
        pwdLengthSlider->hide();
        charTypesWidget->hide();
        cancelButton->hide();
        confirmButton->hide();
        // Enabled actions
        editEntrynameAction->setEnabled(true);
        editUsernameAction->setEnabled(true);
        editPasswordAction->setEnabled(true);
        copyUsernameAction->setEnabled(true);
        copyPasswordAction->setEnabled(true);
        seePasswordAction->setEnabled(true);
        break;

    case AddEntry:
        displayModeLabel->setText(QString(tr("AJOUTER UNE ENTREE")));
        // Lines
        entrynameLine->clear();
        usernameLine->clear();
        passwordLine->clear();
        entrynameLine->setReadOnly(false);
        usernameLine->setReadOnly(false);
        passwordLine->setEchoMode(QLineEdit::Password);
        // Hidden widgets
        pwdLengthSlider->clear();
        charTypesWidget->clear();
        pwdLengthSlider->show();
        charTypesWidget->show();
        cancelButton->show();
        confirmButton->show();
        // Enabled actions
        editEntrynameAction->setEnabled(false);
        editUsernameAction->setEnabled(false);
        editPasswordAction->setEnabled(false);
        copyUsernameAction->setEnabled(false);
        copyPasswordAction->setEnabled(false);
        seePasswordAction->setEnabled(false);
        break;

    case EditEntryname:
        displayModeLabel->setText(QString(tr("MODIFIER LE NOM D'ENTREE")));
        // Lines
        entrynameLine->setReadOnly(false);
        // Enabled actions
        editEntrynameAction->setEnabled(true);
        editUsernameAction->setEnabled(false);
        editPasswordAction->setEnabled(false);
        copyUsernameAction->setEnabled(false);
        copyPasswordAction->setEnabled(false);
        seePasswordAction->setEnabled(false);
        break;

    case EditUsername:
        displayModeLabel->setText(QString(tr("MODIFIER LE NOM D'UTILISATEUR")));
        // Lines
        usernameLine->setReadOnly(false);
        // Enabled actions
        editEntrynameAction->setEnabled(false);
        editUsernameAction->setEnabled(true);
        editPasswordAction->setEnabled(false);
        copyUsernameAction->setEnabled(false);
        copyPasswordAction->setEnabled(false);
        seePasswordAction->setEnabled(false);
        break;

    case EditPassword:
        displayModeLabel->setText(QString(tr("MODIFIER LE MOT DE PASSE")));
        // Lines
        entrynameLine->setReadOnly(true);
        usernameLine->setReadOnly(true);
        passwordLine->setEchoMode(QLineEdit::Password);
        // Hidden widgets
        pwdLengthSlider->setValue(passwordLine->text().size());
        charTypesWidget->clear();
        pwdLengthSlider->show();
        charTypesWidget->show();
        cancelButton->show();
        confirmButton->show();
        // Enabled actions
        editEntrynameAction->setEnabled(false);
        editUsernameAction->setEnabled(false);
        editPasswordAction->setEnabled(false);
        copyUsernameAction->setEnabled(false);
        copyPasswordAction->setEnabled(false);
        seePasswordAction->setEnabled(false);
        break;

    case DeleteEntry:
        displayModeLabel->setText(QString(tr("SUPPRIMER UNE ENTREE")));
        // Hidden widgets
        cancelButton->show();
        confirmButton->show();
        // Enabled actions
        editEntrynameAction->setEnabled(false);
        editUsernameAction->setEnabled(false);
        editPasswordAction->setEnabled(false);
        copyUsernameAction->setEnabled(false);
        copyPasswordAction->setEnabled(false);
        seePasswordAction->setEnabled(false);
        break;

    default: break;
    }
}

void EntryInteractionWidget::reversePasswordEchoMode()
{
    if (passwordLine->echoMode() == QLineEdit::Password)
        passwordLine->setEchoMode(QLineEdit::Normal);
    else
        passwordLine->setEchoMode(QLineEdit::Password);
}

void EntryInteractionWidget::usernameToClipboard()
{
    QString username = usernameLine->text();
    if (username.isEmpty())
        return;
    clipboard->setText(username);
}

void EntryInteractionWidget::passwordToClipboard()
{
    QString password = passwordLine->text();
    if (password.isEmpty())
        return;
    clipboard->setText(password);
}

} // namespace pwm
