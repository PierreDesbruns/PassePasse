// Copyright (C) 2025 Pierre Desbruns
// SPDX-License-Identifier: LGPL-3.0-only

#include "searchmodel.h"

namespace pwm {

SearchModel::SearchModel(EntryManager* entryManager, QObject *parent)
    : QAbstractListModel{parent}, entryManager(entryManager)
{
    connect(entryManager, &EntryManager::entryAdded, this, &SearchModel::updateEntrynames);
    connect(entryManager, &EntryManager::entryDeleted, this, &SearchModel::updateEntrynames);
    connect(entryManager, &EntryManager::entryEdited, this, &SearchModel::updateEntrynames);
    connect(entryManager, &EntryManager::entriesLoaded, this, &SearchModel::updateEntrynames);
}

int SearchModel::rowCount(const QModelIndex& /*parent*/) const
{
    return entrynames.size();
}

QVariant SearchModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= entrynames.size())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return entrynames.at(index.row());

    return QVariant();
}

void SearchModel::updateEntrynames()
{
    entrynames.clear();

    foreach (const Entry& entry, entryManager->entryList())
        entrynames << entry.entryname();

    entrynames.removeDuplicates();

    // Emitting update signal
    QModelIndex topLeft = createIndex(0,0);
    QModelIndex bottomRight = createIndex(rowCount(), 0);
    emit dataChanged(topLeft, bottomRight);
}

} // namespace pwm
