// Copyright (C) 2026 Pierre Desbruns
// SPDX-License-Identifier: LGPL-3.0-only

#include "loginwindow.h"

namespace pwm {

LoginWindow::LoginWindow(QWidget *parent)
    : QDialog{parent}
{
    setWindowTitle("Passepasse - " + tr("Authentification"));
    setFixedSize(windowSmallSize);

    // Labels
    passwordLabel = new QLabel(QString(tr("Mot de passe")));
    newPasswordLabel = new QLabel(QString(tr("Nouveau")));
    confirmNewPasswordLabel = new QLabel(QString(tr("Confirmation")));

    // Line edits
    passwordLine = new QLineEdit();
    passwordLine->setEchoMode(QLineEdit::Password);
    passwordLine->setMaxLength(MASTER_MAXLEN);
    newPasswordLine = new QLineEdit();
    newPasswordLine->setEchoMode(QLineEdit::Password);
    newPasswordLine->setMaxLength(MASTER_MAXLEN);
    confirmNewPasswordLine = new QLineEdit();
    confirmNewPasswordLine->setEchoMode(QLineEdit::Password);
    confirmNewPasswordLine->setMaxLength(MASTER_MAXLEN);

    // Buttons
    confirmButton = new QPushButton(QString(tr("Confirmer")));
    cancelButton = new QPushButton(QString(tr("Annuler")));
    changePwdButton = new QPushButton(QString(tr("Changer")));
    confirmButton->setDefault(true);

    // Layout
    formLayout = new QFormLayout();
    formLayout->addRow(passwordLabel, passwordLine);
    formLayout->addRow(newPasswordLabel, newPasswordLine);
    formLayout->addRow(confirmNewPasswordLabel, confirmNewPasswordLine);
    formLayout->setRowVisible(1, false);
    formLayout->setRowVisible(2, false);

    buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(changePwdButton);
    buttonsLayout->addWidget(confirmButton);
    buttonsLayout->addWidget(cancelButton);

    mainLayout = new QVBoxLayout();
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonsLayout);

    mainContent = new QWidget(this);
    mainContent->setFixedSize(windowSmallSize);
    mainContent->setLayout(mainLayout);

    // Signals / slots
    connect(changePwdButton, SIGNAL(pressed()), this, SLOT(changePassword()));
    connect(cancelButton, SIGNAL(pressed()), this, SLOT(reject()));
    connect(confirmButton, &QPushButton::pressed, this, &LoginWindow::accept);
}

void LoginWindow::accept()
{
    const QString password = passwordLine->text();
    const QString newPassword = newPasswordLine->text();
    const int newPasswordLength = newPassword.size();

    // Uncomment only if master password hash file is empty.
    // updateMasterHash(password);

    if (!pwmsecurity::masterIsCorrect(password))
    {
        // Wrong password
        QMessageBox::critical(
            this,
            this->windowTitle(),
            tr("Mot de passe incorrect.")
            );
        return;
    }

    if (!newPassword.isEmpty())
    {
        // Password changed
        if (newPassword != confirmNewPasswordLine->text())
        {
            // New password and confirmation do not match
            QMessageBox::critical(
                this,
                this->windowTitle(),
                tr("Veuillez entrer deux fois le même mot de passe.")
            );
            return;
        }

        if (newPasswordLength <= MASTER_MINLEN)
        {
            // Password too short (too big covered with line max length, cf. constructor)
            QMessageBox::critical(
                this,
                this->windowTitle(),
                tr("Mot de passe trop court.")
            );
            return;
        }

        if (newPassword == password)
        {
            // New password same as old
            QMessageBox::information(
                this,
                this->windowTitle(),
                tr("Nouveau mot de passe identique à l'ancien.\nAncien mot de passe conservé.")
                );
        }
        else
        {
            pwmsecurity::updateMasterHash(newPassword);

            QMessageBox::information(
                this,
                this->windowTitle(),
                tr("Mot de passe modifié avec succès.")
                );
        }
    }

    emit authentified(password, newPassword);
    QDialog::accept();
}

void LoginWindow::changePassword()
{
    // Resizing window
    setFixedSize(windowLargeSize);
    mainContent->setFixedSize(windowLargeSize);

    // Showing widgets
    formLayout->setRowVisible(1, true);
    formLayout->setRowVisible(2, true);
    passwordLabel->setText(tr("Ancien"));
    changePwdButton->setVisible(false);
}

} // namespace pwm
