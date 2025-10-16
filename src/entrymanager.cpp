#include "entrymanager.h"

namespace pwm {

EntryManager::EntryManager(QObject* parent)
    : QObject{parent}
{

}

void EntryManager::addEntry(const Entry &entry)
{
    // Verifications
    if (m_entryList.contains(entry))
    {
        qWarning() << "Entry Manager: Entry already exists. Did not add entry.";
        return;
    }

    if (entry.password().isEmpty())
    {
        qWarning() << "Entry: Generated password is empty. Did not add entry.";
        return;
    }

    // Entry list update
    m_entryList << entry;

    // entryAdded signal
    emit entryAdded();
}

} // namespace pwm
