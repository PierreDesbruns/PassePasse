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

} // namespace pwm
