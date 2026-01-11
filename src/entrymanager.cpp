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
        qWarning() << "Entry Manager: Given entry name is empty. Did not add entry.";
        return;
    }
    if (entry.username().isEmpty())
    {
        qWarning() << "Entry Manager: Given user name is empty. Did not add entry.";
        return;
    }
    if (entry.password().isEmpty())
    {
        qWarning() << "Entry Manager: Generated password is empty. Did not add entry.";
        return;
    }
    if (m_entryList.contains(entry))
    {
        qWarning() << "Entry Manager: Entry already exists. Did not add entry.";
        return;
    }

    // Entry list update
    m_entryList << entry;

    // Saving entries
    saveEntries();

    emit entryAdded(entry);
    emit entryListChanged(m_entryList);
}

void EntryManager::delEntry(const Entry &entry)
{
    // Verifications
    int entryIndex = m_entryList.indexOf(entry);
    if (entry.entryname().isEmpty())
    {
        qWarning() << "Entry Manager: Given entry name is empty. Did not delete entry.";
        return;
    }
    if (entry.username().isEmpty())
    {
        qWarning() << "Entry Manager: Given user name is empty. Did not delete entry.";
        return;
    }
    if (entryIndex == -1)
    {
        qWarning() << "Entry Manager: Entry does not exist. Did not delete entry.";
        return;
    }

    // Removing entry
    m_entryList.removeAt(entryIndex);

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
        qWarning() << "Entry Manager: Entry does not exist. Did not reset entry.";
        return;
    }

    // Checking for error in password generation
    if (entry.password().isEmpty())
    {
        qWarning() << "Entry Manager: Generated password is empty. Did not reset entry.";
        return;
    }

    // Replacing entry
    m_entryList.replace(entryIndex, entry);

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
        qWarning() << "Entry Manager: Entry not found. Did not edit entry.";
        return;
    }

    // Checking potential doubles
    if (m_entryList.contains(newEntry))
    {
        qWarning() << "Entry Manager: Given entry already exists. Did not edit entry.";
        return;
    }

    // Replacing entry
    Entry entry = m_entryList.at(entryIndex);
    if (!newEntry.entryname().isEmpty())
        entry.setEntryname(newEntry.entryname());
    if (!newEntry.username().isEmpty())
        entry.setUsername(newEntry.username());
    m_entryList.replace(entryIndex, entry);

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
    if (pwmsecurity::writeEntries(m_masterPassword, entrynames, usernames, passwords, dates) != 0)
    {
        // Error in file writing
        qFatal() << "Entry Manager: Error while writing entries in file.";
        return nbEntriesWritten;
    }

    nbEntriesWritten = entrynames.size();

    qInfo() << "Entry Manager: Successfully saved" << nbEntriesWritten << "entries.";

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
        qWarning() << "No entry loaded. Entry file may be empty.";
        return nbEntriesLoaded;
    }

    // Converting QStringList to QList<Entry>
    for (const QString& entry : entriyList_QString)
    {
        QStringList fields = entry.split('\t');
        if (fields.size() != 4)
            qWarning() << "Format of entry" << entriyList_QString.indexOf(entry) <<  "is incorrect. Skipped entry.";
        else
        {
            entryList << Entry(fields[0], fields[1], fields[2], fields[3]);
            nbEntriesLoaded++;
        }
    }

    m_entryList = entryList;

    qInfo() << "Entry Manager: Successfully loaded" << nbEntriesLoaded << "entries.";

    emit entriesLoaded();
    emit entryListChanged(m_entryList);

    return nbEntriesLoaded;
}

} // namespace pwm
