#include "entrylistmodel.h"


namespace pwm {

EntryListModel::EntryListModel(QObject *parent)
    : QAbstractListModel{parent}
{

}

int EntryListModel::rowCount(const QModelIndex& /*parent*/) const
{
    if (entrynames.size() != usernames.size())
        qWarning() << "Number of entrynames and usernames are different.";

    return entrynames.size();
}

QVariant EntryListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= entrynames.size())
        return QVariant();

    if (role == Qt::DisplayRole)
        return entrynames.at(index.row());

    if (role == Qt::UserRole)
        return usernames.at(index.row());

    return QVariant();
}

void EntryListModel::setLists(const QStringList& newEntrynames, const QStringList& newUsernames)
{
    if (newEntrynames.size() != newUsernames.size())
    {
        qWarning() << "Given entry and user names do no have same size. Did not set lists.";
        return;
    }

    entrynames = newEntrynames;
    usernames = newUsernames;
}

} // namespace pwm
