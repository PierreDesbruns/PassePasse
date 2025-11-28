// Copyright (C) 2025 Pierre Desbruns
// SPDX-License-Identifier: LGPL-3.0-only

#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include <QSize>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "pwmsecurity.h"


namespace pwm {

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    LoginWindow(QWidget* parent = nullptr);
    QString getPassword() const { return passwordLine->text(); }
    QString getNewPassword() const { return (newPasswordLine->text().isEmpty() ? getPassword() : newPasswordLine->text()); }

private slots:
    /**
     * @brief Close window with Accecpted result code after verifications.
     *
     * Called when confirm button is pressed.
     * Verifications:
     * 1. Password must be correct.
     * 2. (if password changed) New password and confirmation must match.
     * 3. (if password changed) New password must be long enough.
     */
    void accept() override;
    /**
     * @brief Set change password interface to visible.
     * Update [passwordChanged] to true.
     */
    void changePassword();

signals:
    void authentified(const QString& master, const QString& newMaster);

private:
    const QSize windowSmallSize = QSize(300,90);
    const QSize windowLargeSize = QSize(300,140);

//    bool passwordChanged = false; // flag to indicate if user asks to change master password

    QWidget *mainContent;

    QVBoxLayout *mainLayout;
    QFormLayout *formLayout;
    QHBoxLayout *buttonsLayout;

    QLabel *passwordLabel;
    QLabel *newPasswordLabel;
    QLabel *confirmNewPasswordLabel;

    QLineEdit *passwordLine;
    QLineEdit *newPasswordLine;
    QLineEdit *confirmNewPasswordLine;

    QPushButton *confirmButton;
    QPushButton *cancelButton;
    QPushButton *changePwdButton;
};

} // namespace pwm

#endif // LOGINWINDOW_H
