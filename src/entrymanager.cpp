#include "entrymanager.h"

namespace pwm {

EntryManager::EntryManager(QObject* parent)
    : QObject{parent}
{

}

void EntryManager::addEntry(const Entry& entry)
{
    // Verifications
    if (m_entryList.contains(entry))
    {
        qWarning() << "Entry Manager: Entry already exists. Did not add entry.";
        return;
    }

    if (entry.password().isEmpty())
    {
        qWarning() << "Entry Manager: Generated password is empty. Did not add entry.";
        return;
    }

    // Entry list update
    m_entryList << entry;

    emit entryAdded();
}

void EntryManager::resetEntry(const Entry& entry)
{
    // Searching for given entry
    int entryIndex = m_entryList.indexOf(entry);
    if (entryIndex == -1)
    {
        qWarning() << "Entry Manager: Entry not found. Did not reset entry.";
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

    emit entryReset();
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

    emit entryEdited();
}

} // namespace pwm
