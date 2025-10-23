// Copyright (C) 2025 Pierre Desbruns
// SPDX-License-Identifier: LGPL-3.0-only

#ifndef ENTRYINTERACTIONWIDGET_H
#define ENTRYINTERACTIONWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QAction>
#include <QIcon>

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

    enum DisplayMode { EntryInfo, AddEntry, EditEntryname, EditUsername, EditPassword };

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
     * @brief Change display mode to AddEntry.
     */
    void triggerAddEntryMode();
    /**
     * @brief Change display mode to EditEntryname.
     */
    void triggerEditEntrynameMode();
    /**
     * @brief Change display mode to EditUsername.
     */
    void triggerEditUsernameMode();
    /**
     * @brief Change display mode to EditPassword.
     */
    void triggerEditPasswordMode();
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
     * @brief Confirm add or edit action and set display mode to entry info.
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
     * @brief Emitted when an entry addition is confirmed.
     * @param entry: Entry be added.
     */
    void addEntryConfirmed(const Entry& entry);
    /**
     * @brief Emitted when a password edition is confirmed.
     * @param entry: Entry with new password.
     */
    void editPasswordConfirmed(const Entry& entry);
    /**
     * @brief Emitted when an entry name edition is confirmed.
     * @param newEntry: Entry with new entry name.
     * @param oldEntry: Entry to be replaced.
     */
    void editEntrynameConfirmed(const Entry& newEntry, const Entry& oldEntry);
    /**
     * @brief Emitted when a user name edition is confirmed.
     * @param newEntry: ENtry with new user name.
     * @param oldEntry: Entry to be replaced.
     */
    void editUsernameConfirmed(const Entry& newEntry, const Entry& oldEntry);

private:
    // Attributes
    DisplayMode m_displayMode;

    EntryManager* entryManager;

    // Widgets
    QVBoxLayout* mainLayout;

    QLabel* displayModeLabel;
    QLabel* entrynameLabel;
    QLabel* usernameLabel;
    QLabel* passwordLabel;

    QLineEdit* entrynameLine;
    QLineEdit* usernameLine;
    QLineEdit* passwordLine;

    QAction* editEntrynameAction;
    QAction* editUsernameAction;
    QAction* editPasswordAction;
    QAction* copyUsernameAction;
    QAction* copyPasswordAction;
    QAction* seePasswordAction;

    QPushButton* confirmButton;
    QPushButton* cancelButton;

    PasswordLengthSlider* pwdLengthSlider;

    CharacterTypesWidget* charTypesWidget;
};

} // namespace pwm

#endif // ENTRYINTERACTIONWIDGET_H
