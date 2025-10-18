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
#include "entrymanager.h"


namespace pwm {

class EntryInteractionWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(DisplayMode displayMode READ displayMode WRITE setDisplayMode NOTIFY displayModeChanged)

public:
    explicit EntryInteractionWidget(EntryManager* entryManager, QWidget* parent = nullptr);

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
    /**
     * @brief Change display to AddEntry.
     */
    void triggerAddMode();
    /**
     * @brief Change display to ResetPassword.
     */
    void triggerResetMode();
    /**
     * @brief Setter of [entryname], [username], and [password].
     * @param entryname, username: Entry info to be displayed.
     * Trigger updateDisplay().
     */
    void displayEntry(const Entry& entry);
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
    /**
     * @brief Show/Hide password.
     */
    void reversePasswordEchoMode();

signals:
    void displayModeChanged(const DisplayMode newDisplayMode);
    /**
     * @brief Emitted when an entry add is confirmed.
     * @param entry: Entry be added.
     */
    void addEntryConfirmed(const Entry& entry);
    /**
     * @brief Emitted when an entry's password reset is confirmed.
     * @param entry: Entry with new password.
     */
    void resEntryConfirmed(const Entry& entry);

private:
    // Attributes
    DisplayMode m_displayMode;

    EntryManager* entryManager;

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
