#ifndef ENTRYMANAGER_H
#define ENTRYMANAGER_H

#include <QObject>
#include <QList>
#include <QStringList>
#include <QString>
#include <QDebug>
#include <QMessageBox>

#include "entry.h"
#include "pwmsecurity.h"


namespace pwm {

class EntryManager : public QObject
{
    Q_OBJECT

public:
    explicit EntryManager(QObject* parent = nullptr);

    QList<Entry> entryList() const { return m_entryList; }

public slots:
    /**
     * @brief Initialize entry manager.
     * @param master: Master password for file encryption/
     * @param newMaster: New master password if changed by user.
     *
     * Load entries and save with new master if changed by user.
     */
    void init(const QString& master, const QString& newMaster);
    /**
     * @brief Add given entry to entry list.
     */
    void addEntry(const Entry& entry);
    /**
     * @brief Delete given entry from entry list.
     */
    void delEntry(const Entry& entry);
    /**
     * @brief Reset password of an entry by replacing it by given entry.
     */
    void resetEntry(const Entry& entry);
    /**
     * @brief Edit entry or user name of desired entry.
     * @param newEntry: Entry with new entry/user name.
     * @param oldEntry: Entry to be replaced.
     */
    void editEntry(const Entry& newEntry, const Entry& oldEntry);

signals:
    void entryAdded(const Entry& entry);
    void entryDeleted(const Entry& entry);
    void entryReset(const Entry& entry);
    void entryEdited(const Entry& entry);
    void entriesLoaded();
    void entryListChanged(const QList<Entry>& newEntryList);

private:
    QList<Entry> m_entryList;

    QString m_masterPassword;

    /**
     * @brief Save entries to entries file.
     * @return Number of entries saved.
     */
    int saveEntries() const;
    /**
     * @brief Load entries from entries file.
     * @return Number of entries loaded.
     */
    int loadEntries();
};

} // namespace pwm

#endif // ENTRYMANAGER_H
