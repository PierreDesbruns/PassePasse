// Copyright (C) 2025 Pierre Desbruns
// SPDX-License-Identifier: LGPL-3.0-only

#include "entry.h"

namespace pwm {

Entry::Entry(const QString& entryname, const QString& username)
    : m_entryname(entryname), m_username(username), m_password(""), m_date("")
{

}

Entry::Entry(const QString& entryname, const QString& username, const QString& password, const QString& date)
    : m_entryname(entryname), m_username(username), m_password(password), m_date(date)
{

}

Entry::Entry(const QString& entryname, const QString& username, const int passwordLength, const int characterTypes)
    : m_entryname(entryname), m_username(username)
{
    setPassword(passwordLength, characterTypes);
}

bool Entry::operator==(const Entry& other) const
{
    if ((other.entryname() == m_entryname) && (other.username() == m_username))
        return true;
    return false;
}

QString Entry::entryname() const
{
    return m_entryname;
}

void Entry::setEntryname(const QString& entryname)
{
    if (entryname.isEmpty())
        qWarning() << "Set entry with an empty entry name.";

    m_entryname = entryname;
}

QString Entry::username() const
{
    return m_username;
}

void Entry::setUsername(const QString& username)
{
    if (username.isEmpty())
        qWarning() << "Set entry with an empty user name.";

    m_username = username;
}

QString Entry::password() const
{
    return m_password;
}

void Entry::setPassword(const int passwordLength, const int characterTypes)
{
    if (passwordLength < 1)
    {
        qCritical() << "Tried to set entry's password with too small password length. Aborted set password.";
        return;
    }
    if ((characterTypes < 0) || (characterTypes > 15))
    {
        qWarning() << "Tried to set entry's password with invalid character type format. Aborted set password.";
        return;
    }

    // Password generation
    bool hasLowCase = ((characterTypes & 0b1000) != 0);
    bool hasUpCase = ((characterTypes & 0b0100) != 0);
    bool hasNumbers = ((characterTypes & 0b0010) != 0);
    bool hasSpecials = ((characterTypes & 0b0001) != 0);

    QString password = pwmsecurity::generatePassword(passwordLength, hasLowCase, hasUpCase, hasNumbers, hasSpecials);

    if (password.isEmpty())
    {
        qCritical() << "Tried to set entry's password with empty generated password. Aborted set password.";
        return;
    }

    m_password = password;
    m_date = QDate::currentDate().toString("yyyy.MM.dd");
}

QString Entry::date() const
{
    return m_date;
}

} // namespace pwm
