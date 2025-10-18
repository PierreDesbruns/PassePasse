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
     * @brief Add given entry to entry list.
     */
    void addEntry(const Entry& entry);
    /**
     * @brief Reset password of an entry by replacing it by given entry.
     */
    void resetEntry(const Entry& entry);

signals:
    void entryAdded();
    void entryReset();

private:
    QList<Entry> m_entryList;

};

} // namespace pwm

#endif // ENTRYMANAGER_H
