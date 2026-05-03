// Copyright (C) 2026 Pierre Desbruns
// SPDX-License-Identifier: LGPL-3.0-only

#include "entrymanager.h"

namespace pwm {

EntryManager::EntryManager(QObject* parent)
    : QObject{parent}
{

}

void EntryManager::init(const QString& master, const QString& newMaster)
{
    m_masterPassword = master;

    loadEntries();

    if (newMaster.isEmpty())
        // Master password not changed
        return;

    m_masterPassword = newMaster;

    // Saving entries in case master password has changed
    saveEntries();
}

void EntryManager::addEntry(const Entry& entry)
{
    // Verifications
    if (entry.entryname().isEmpty())
    {
        qCritical() << "Tried to add an entry with empty entry name. Aborted add entry.";
        return;
    }
    if (entry.username().isEmpty())
    {
        qCritical() << "Tried to add an entry with empty user name. Aborted add entry.";
        return;
    }
    if (entry.password().isEmpty())
    {
        qCritical() << "Tried to add an entry with empty password. Aborted add entry.";
        return;
    }
    if (m_entryList.contains(entry))
    {
        qCritical() << "Tried to add an entry that already exists. Aborted add entry.";
        return;
    }

    // Entry list update
    m_entryList << entry;

    qInfo() << "Entry successfully added.";

    // Saving entries
    saveEntries();

    emit entryAdded(entry);
    emit entryListChanged(m_entryList);
}

void EntryManager::delEntry(const Entry& entry)
{
    // Verifications
    int entryIndex = m_entryList.indexOf(entry);
    if (entry.entryname().isEmpty())
    {
        qCritical() << "Tried to delete an entry with empty entry name. Aborted delete entry.";
        return;
    }
    if (entry.username().isEmpty())
    {
        qCritical() << "Tried to delete an entry with empty user name. Aborted delete entry.";
        return;
    }
    if (entryIndex == -1)
    {
        qCritical() << "Tried to delete an entry that does not exist. Aborted delete entry.";
        return;
    }

    // Removing entry
    m_entryList.removeAt(entryIndex);

    qInfo() << "Entry successfully deleted.";

    // Saving entries
    saveEntries();

    emit entryDeleted(entry);
    emit entryListChanged(m_entryList);
}

void EntryManager::resetEntry(const Entry& entry)
{
    // Searching for given entry
    int entryIndex = m_entryList.indexOf(entry);
    if (entryIndex == -1)
    {
        qCritical() << "Tried to reset an entry that does not exist. Aborted reset entry.";
        return;
    }

    // Checking for error in password generation
    if (entry.password().isEmpty())
    {
        qCritical() << "Tried to reset an entry with empty password. Aborted reset entry.";
        return;
    }

    // Replacing entry
    m_entryList.replace(entryIndex, entry);

    qInfo() << "Entry successfully reset.";

    // Saving entries
    saveEntries();

    emit entryReset(entry);
    emit entryListChanged(m_entryList);
}

void EntryManager::editEntry(const Entry& newEntry, const Entry& oldEntry)
{
    // Searching for original entry
    int entryIndex = m_entryList.indexOf(oldEntry);
    if (entryIndex == -1)
    {
        qCritical() << "Tried to edit an entry that does not exist. Aborted entry edit.";
        return;
    }

    // Checking potential doubles
    if (m_entryList.contains(newEntry))
    {
        qCritical() << "Tried to edit an entry into an entry that already exists. Aborted entry edit.";
        return;
    }

    // Replacing entry
    Entry entry = m_entryList.at(entryIndex);
    if (!newEntry.entryname().isEmpty())
        entry.setEntryname(newEntry.entryname());
    if (!newEntry.username().isEmpty())
        entry.setUsername(newEntry.username());
    m_entryList.replace(entryIndex, entry);

    qInfo() << "Entry successfully edited.";

    // Saving entry
    saveEntries();

    emit entryEdited(entry);
    emit entryListChanged(m_entryList);
}

int EntryManager::saveEntries() const
{
    int nbEntriesWritten = 0;

    // QString lists
    QStringList entrynames;
    QStringList usernames;
    QStringList passwords;
    QStringList dates;

    for (const Entry& entry : m_entryList)
    {
        entrynames << entry.entryname();
        usernames << entry.username();
        passwords << entry.password();
        dates << entry.date();
    }

    // Writing entries in file
    nbEntriesWritten = pwmsecurity::writeEntries(m_masterPassword, entrynames, usernames, passwords, dates);
    if (nbEntriesWritten < 0)
    {
        // Error in file writing
        qCritical() << "Failed to write entries in file. Aborted save entries.";
        return 0;
    }

    qInfo() << "Successfully saved" << nbEntriesWritten << "entries.";

    return nbEntriesWritten;
}

int EntryManager::loadEntries()
{
    int nbEntriesLoaded = 0;

    // Temporary list
    QList<Entry> entryList;

    // Reading file
    QStringList entriyList_QString = pwmsecurity::readEntries(m_masterPassword);
    if (entriyList_QString.isEmpty())
    {
        // Empty file or error in entries file reading
        qWarning() << "No entry loaded. Entry file may be empty or an error occured during entry file reading.";
        return 0;
    }

    // Converting QStringList to QList<Entry>
    for (const QString& entry : entriyList_QString)
    {
        QStringList fields = entry.split('\t');
        if (fields.size() != 4)
            qWarning() << "Tried to load an entry with invalid format. Skipped entry.";
        else
        {
            entryList << Entry(fields[0], fields[1], fields[2], fields[3]);
            nbEntriesLoaded++;
        }
    }

    m_entryList = entryList;

    qInfo() << "Successfully loaded" << nbEntriesLoaded << "entries.";

    emit entriesLoaded();
    emit entryListChanged(m_entryList);

    return nbEntriesLoaded;
}

} // namespace pwm
