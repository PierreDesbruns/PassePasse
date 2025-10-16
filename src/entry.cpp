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
        qWarning() << "Entry: Given entry name is empty.";

    m_entryname = entryname;
}

QString Entry::username() const
{
    return m_username;
}

void Entry::setUsername(const QString& username)
{
    if (username.isEmpty())
        qWarning() << "Entry: Given user name is empty.";

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
        qWarning() << "Entry: Given length is too small. Did not set password.";
        return;
    }
    if ((characterTypes < 0) || (characterTypes > 15))
    {
        qWarning() << "Entry: Charater types format not recognized. Did not set password.";
        return;
    }

    // Password generation
    bool hasLowCase = ((characterTypes & 0b1000) != 0);
    bool hasUpCase = ((characterTypes & 0b0100) != 0);
    bool hasNumbers = ((characterTypes & 0b0010) != 0);
    bool hasSpecials = ((characterTypes & 0b0001) != 0);

    QString password = generatePassword(passwordLength, hasLowCase, hasUpCase, hasNumbers, hasSpecials);

    if (password.isEmpty())
    {
        qWarning() << "Entry: Generated password is empty. Did not set password.";
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
