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

void Entry::setEntryname(const QString& newEntryname)
{
    m_entryname = newEntryname;
}

QString Entry::username() const
{
    return m_username;
}

void Entry::setUsername(const QString& newUsername)
{
    m_username = newUsername;
}

QString Entry::password() const
{
    return m_password;
}

void Entry::setPassword(const QString& newPassword)
{
    m_password = newPassword;
    m_date = QDate::currentDate().toString("yyyy.MM.dd");
}

QString Entry::date() const
{
    return m_date;
}

}
