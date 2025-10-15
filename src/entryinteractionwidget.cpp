// Copyright (C) 2025 Pierre Desbruns
// SPDX-License-Identifier: LGPL-3.0-only

#include "entryinteractionwidget.h"

namespace pwm {

EntryInteractionWidget::EntryInteractionWidget(EntryManager* entryManager, QWidget* parent)
    : QWidget{parent}, entryManager(entryManager), m_displayMode(EntryInfo)
{
    // Labels
    entrynameLabel = new QLabel(QString(tr("Nom de l'entrée")));
    usernameLabel = new QLabel(QString(tr("Nom d'utilisateur")));
    passwordLabel = new QLabel(QString(tr("Mot de passe")));

    // Buttons
    editEntrynameButton = new QPushButton(QString(tr("Modifier")));
    editUsernameButton = new QPushButton(QString(tr("Modifier")));
    editPasswordButton = new QPushButton(QString(tr("Modifier")));
    copyUsernameButton = new QPushButton(QString(tr("Copier")));
    copyPasswordButton = new QPushButton(QString(tr("Copier")));
    seePasswordButton = new QPushButton(QString(tr("Voir")));
    confirmButton = new QPushButton(QString(tr("Valider")));
    cancelButton = new QPushButton(QString(tr("Annuler")));

    // Line edits
    entrynameLine = new QLineEdit();
    usernameLine = new QLineEdit();
    passwordLine = new QLineEdit();
    passwordLine->setReadOnly(true);

    // Password slider
    pwdLengthSlider = new PasswordLengthSlider(60);

    // Characters checkboxes
    charTypesWidget = new CharacterTypesWidget();

    // Layout
    mainLayout = new QGridLayout(this);
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(entrynameLabel, 0, 0, Qt::AlignLeft);
    mainLayout->addWidget(editEntrynameButton, 0, 3);
    mainLayout->addWidget(entrynameLine, 1, 0, 1, 4, Qt::AlignTop);
    mainLayout->addWidget(usernameLabel, 2, 0, Qt::AlignLeft);
    mainLayout->addWidget(copyUsernameButton, 2, 2);
    mainLayout->addWidget(editUsernameButton, 2, 3);
    mainLayout->addWidget(usernameLine, 3, 0, 1, 4, Qt::AlignTop);
    mainLayout->addWidget(passwordLabel, 4, 0, Qt::AlignLeft);
    mainLayout->addWidget(seePasswordButton, 4, 1);
    mainLayout->addWidget(copyPasswordButton, 4, 2);
    mainLayout->addWidget(editPasswordButton, 4, 3);
    mainLayout->addWidget(passwordLine, 5, 0, 1, 4, Qt::AlignTop);
    mainLayout->addWidget(pwdLengthSlider, 6, 0, 1, 4);
    mainLayout->addWidget(charTypesWidget, 7, 0, 1, 4);
    mainLayout->addWidget(cancelButton, 8, 0, 1, 2);
    mainLayout->addWidget(confirmButton, 8, 2, 1, 2);

    // Initializations
    updateDisplay(EntryInfo);

    // Slots / signals
    connect(this, SIGNAL(displayModeChanged(DisplayMode)), this, SLOT(updateDisplay(DisplayMode)));
    connect(seePasswordButton, SIGNAL(pressed()), this, SLOT(reversePasswordEchoMode()));
    connect(editPasswordButton, SIGNAL(pressed()), this, SLOT(triggerResetMode()));
    connect(confirmButton, SIGNAL(pressed()), this, SLOT(confirm()));
    connect(cancelButton, SIGNAL(pressed()), this, SLOT(cancel()));
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
    setDisplayMode(EntryInfo);
    entrynameLine->clear();
    usernameLine->clear();
    passwordLine->clear();
}

void EntryInteractionWidget::confirm()
{
    // Getting values from widgets
    QString entryname = entrynameLine->text();
    QString username = usernameLine->text();
    int passwordLength = pwdLengthSlider->value();
    int characterTypes = charTypesWidget->checkedBoxes();

    // Requesting entry manager after verifications
    if (m_displayMode == AddEntry)
    {
        if (!entryname.isEmpty() && !username.isEmpty() && characterTypes)
            entryManager->addEntry(entryname, username, passwordLength, characterTypes);
    }

    // Resetting display
    setDisplayMode(EntryInfo);
    entrynameLine->clear();
    usernameLine->clear();
    passwordLine->clear();
}

void EntryInteractionWidget::updateDisplay(DisplayMode displayMode)
{
    switch (displayMode)
    {
    case EntryInfo:
        entrynameLine->setReadOnly(true);
        usernameLine->setReadOnly(true);
        passwordLine->setEchoMode(QLineEdit::Password);
        pwdLengthSlider->hide();
        pwdLengthSlider->clear();
        charTypesWidget->hide();
        cancelButton->hide();
        confirmButton->hide();
        break;
    case AddEntry:
        entrynameLine->clear();
        usernameLine->clear();
        passwordLine->clear();
        entrynameLine->setReadOnly(false);
        usernameLine->setReadOnly(false);
        pwdLengthSlider->show();
        pwdLengthSlider->clear();
        charTypesWidget->show();
        charTypesWidget->clear();
        cancelButton->show();
        confirmButton->show();
        break;
    case ResetPassword:
        entrynameLine->setReadOnly(true);
        usernameLine->setReadOnly(true);
        passwordLine->setEchoMode(QLineEdit::Password);
        pwdLengthSlider->show();
        pwdLengthSlider->setValue(passwordLine->text().size());
        charTypesWidget->show();
        charTypesWidget->clear();
        cancelButton->show();
        confirmButton->show();
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

} // namespace pwm
