// Copyright (C) 2025 Pierre Desbruns
// SPDX-License-Identifier: LGPL-3.0-only

#ifndef ENTRYINTERACTIONWIDGET_H
#define ENTRYINTERACTIONWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>

#include "charactertypeswidget.h"
#include "passwordlengthslider.h"


namespace pwm {

class EntryInteractionWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(DisplayMode displayMode READ displayMode WRITE setDisplayMode NOTIFY displayModeChanged)

public:
    explicit EntryInteractionWidget(QWidget* parent = nullptr);

    enum DisplayMode { EntryInfo, AddEntry, ResetPassword };

    DisplayMode displayMode() const { return m_displayMode; }
    void setDisplayMode(DisplayMode displayMode)
    {
        if (m_displayMode == displayMode)
            return;
        m_displayMode = displayMode;
        emit displayModeChanged(displayMode);
    }

public slots:
    void triggerAddMode() { setDisplayMode(AddEntry); }
    void triggerResetMode() { setDisplayMode(ResetPassword); }
    /**
     * @brief Setter of [entryname], [username], and [password].
     * @param entryname, username, password: Entry info to be displayed.
     * Trigger updateDisplay().
     */
    void displayEntry(const QString& newEntryname, const QString& newUsername, const QString& newPassword);
    /**
     * @brief Cancel add or reset action and set display mode to entry info.
     */
    void cancel();
    /**
     * @brief Confirm add or reset action and set display mode to entry info.
     */
    void confirm();

private slots:
    /**
     * @brief Manage display according to the display mode.
     */
    void updateDisplay(DisplayMode displayMode);

signals:
    void displayModeChanged(DisplayMode newDisplayMode);

private:
    // Attributes
    DisplayMode m_displayMode;

    QString entryname;
    QString username;
    QString password;

    // Widgets
    QGridLayout* mainLayout;

    QLabel* entrynameLabel;
    QLabel* usernameLabel;
    QLabel* passwordLabel;

    QLineEdit* entrynameLine;
    QLineEdit* usernameLine;
    QLineEdit* passwordLine;

    QPushButton* editEntrynameButton;
    QPushButton* editUsernameButton;
    QPushButton* editPasswordButton;
    QPushButton* copyUsernameButton;
    QPushButton* copyPasswordButton;
    QPushButton* seePasswordButton;
    QPushButton* confirmButton;
    QPushButton* cancelButton;

    PasswordLengthSlider* pwdLengthSlider;

    CharacterTypesWidget* charTypesWidget;
};

} // namespace pwm

#endif // ENTRYINTERACTIONWIDGET_H
