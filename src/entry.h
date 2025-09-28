// Copyright (C) 2025 Pierre Desbruns
// SPDX-License-Identifier: LGPL-3.0-only

#ifndef ENTRY_H
#define ENTRY_H

#include <QString>
#include <QDate>


namespace pwm {

class Entry
{
public:
    Entry() = default;
    ~Entry() = default;
    Entry(const Entry &) = default;
    Entry& operator=(const Entry &) = default;

    Entry(const QString& entryname, const QString& username);
    Entry(const QString& entryname, const QString& username, const QString& password, const QString& date);

    bool operator==(const Entry& other) const;

    QString entryname() const;
    void setEntryname(const QString& newEntryname);

    QString username() const;
    void setUsername(const QString& newUsername);

    QString password() const;
    void setPassword(const QString& newPassword);

    QString date() const;

private:
    QString m_entryname;
    QString m_username;
    QString m_password;
    QString m_date;
};

} // namepsace pwm

Q_DECLARE_METATYPE(pwm::Entry)

#endif // ENTRY_H
