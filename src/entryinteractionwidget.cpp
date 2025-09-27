// Copyright (C) 2025 Pierre Desbruns
// SPDX-License-Identifier: LGPL-3.0-only

#include "entryinteractionwidget.h"

namespace pwm {

EntryInteractionWidget::EntryInteractionWidget(QWidget *parent)
    : QWidget{parent}, m_displayMode(EntryInfo), entryname(""), username(""), password("")
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
    connect(editPasswordButton, SIGNAL(pressed()), this, SLOT(triggerResetMode()));
    connect(confirmButton, SIGNAL(pressed()), this, SLOT(confirm()));
    connect(cancelButton, SIGNAL(pressed()), this, SLOT(cancel()));
}

void EntryInteractionWidget::displayEntry(const QString& newEntryname, const QString& newUsername, const QString& newPassword)
{
    entryname = newEntryname;
    username = newUsername;
    password = newPassword;
    setDisplayMode(EntryInfo);
}

void EntryInteractionWidget::cancel()
{
    entryname = "";
    username = "";
    password = "";
    setDisplayMode(EntryInfo);
}

void EntryInteractionWidget::confirm()
{
    entryname = "";
    username = "";
    password = "";
    setDisplayMode(EntryInfo);
}

void EntryInteractionWidget::updateDisplay(DisplayMode displayMode)
{
    switch (displayMode)
    {
    case EntryInfo:
        entrynameLine->setReadOnly(true);
        entrynameLine->setText(entryname);
        usernameLine->setReadOnly(true);
        usernameLine->setText(username);
        passwordLine->setReadOnly(true);
        passwordLine->setEchoMode(QLineEdit::Password);
        passwordLine->setText(password);
        pwdLengthSlider->hide();
        pwdLengthSlider->clear();
        charTypesWidget->hide();
        charTypesWidget->clear();
        cancelButton->hide();
        confirmButton->hide();
        break;
    case AddEntry:
        entrynameLine->setReadOnly(false);
        entrynameLine->setText("");
        usernameLine->setReadOnly(false);
        usernameLine->setText("");
        passwordLine->setReadOnly(true);
        passwordLine->setEchoMode(QLineEdit::Password);
        passwordLine->setText("");
        pwdLengthSlider->show();
        charTypesWidget->show();
        cancelButton->show();
        confirmButton->show();
        break;
    case ResetPassword:
        entrynameLine->setReadOnly(true);
        entrynameLine->setText(entryname);
        usernameLine->setReadOnly(true);
        usernameLine->setText(username);
        passwordLine->setReadOnly(true);
        passwordLine->setEchoMode(QLineEdit::Password);
        passwordLine->setText(password);
        pwdLengthSlider->show();
        charTypesWidget->show();
        cancelButton->show();
        confirmButton->show();
        break;
    default: break;
    }
}

} // namespace pwm
