// Copyright (C) 2025 Pierre Desbruns
// SPDX-License-Identifier: LGPL-3.0-only

#include "entrylistmodel.h"

namespace pwm {

EntryListModel::EntryListModel(QObject *parent)
    : QAbstractListModel{parent}
{

}

int EntryListModel::rowCount(const QModelIndex& /*parent*/) const
{
    if (entrynames.size() != usernames.size())
    {
        qWarning() << "Number of entrynames and usernames are different. Returned -1 as row count.";
        return -1;
    }

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

void EntryListModel::updateLists(const QStringList& newEntrynames, const QStringList& newUsernames)
{
    if (newEntrynames.size() != newUsernames.size())
    {
        qWarning() << "Given entry and user names do no have same size. Did not set lists.";
        return;
    }

    // Updating lists
    entrynames = newEntrynames;
    usernames = newUsernames;

    // Creating index and emitting update signal
    QModelIndex topLeft = createIndex(0,0);
    QModelIndex bottomRight = createIndex(rowCount(), 0);
    emit dataChanged(topLeft, bottomRight);
}

} // namespace pwm
