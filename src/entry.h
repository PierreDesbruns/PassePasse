// Copyright (C) 2025 Pierre Desbruns
// SPDX-License-Identifier: LGPL-3.0-only

#ifndef ENTRY_H
#define ENTRY_H

#include <QString>
#include <QDate>

#include "pwmsecurity.h"


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
    Entry(const QString& entryname, const QString& username, const int passwordLength, const int characterTypes);

    bool operator==(const Entry& other) const;

    QString entryname() const;
    void setEntryname(const QString& entryname);

    QString username() const;
    void setUsername(const QString& username);

    QString password() const;
    void setPassword(const int passwordLength, const int characterTypes);

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
