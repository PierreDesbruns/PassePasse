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

    /**
     * @brief Return password of entry corresponding to entry and user names.
     */
    QString passwordOf(const QString& entryname, const QString& username);

public slots:
    /**
     * @brief Generate password and add given entry to [entryList].
     */
    void addEntry(const QString& entryname, const QString& username, const int passwordLength, const int characterTypes);

signals:
    void entryAdded(const QStringList& entrynames, const QStringList& usernames);

private:
    QList<Entry> m_entryList;

};

} // namespace pwm

#endif // ENTRYMANAGER_H
