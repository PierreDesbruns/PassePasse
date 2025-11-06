// Copyright (C) 2025 Pierre Desbruns
// SPDX-License-Identifier: LGPL-3.0-only

#include "entrylistmodel.h"

namespace pwm {

EntryListModel::EntryListModel(EntryManager* entryManager, QObject *parent)
    : QAbstractListModel{parent}, entryManager(entryManager)
{
    // Signals / slots
    connect(entryManager, &EntryManager::entryAdded, this, &EntryListModel::reset);
    connect(entryManager, &EntryManager::entryDeleted, this, &EntryListModel::reset);
    connect(entryManager, &EntryManager::entryEdited, this, &EntryListModel::reset);
}

int EntryListModel::rowCount(const QModelIndex& /*parent*/) const
{
    return entries.size();
}

QVariant EntryListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= entries.size())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return QVariant::fromValue<Entry>(entries.at(index.row()));

    return QVariant();
}

void EntryListModel::filter(const QString& filter)
{
    if (filter.isEmpty())
    {
        reset();
        return;
    }

    entries.clear();

    foreach (const Entry& entry, entryManager->entryList())
    {
        if (entry.entryname() == filter)
            entries << entry;
    }

    // Emitting update signal
    QModelIndex topLeft = createIndex(0,0);
    QModelIndex bottomRight = createIndex(rowCount(), 0);
    emit dataChanged(topLeft, bottomRight);
}

void EntryListModel::reset()
{
    entries = entryManager->entryList();

    // Emitting update signal
    QModelIndex topLeft = createIndex(0,0);
    QModelIndex bottomRight = createIndex(rowCount(), 0);
    emit dataChanged(topLeft, bottomRight);
}

} // namespace pwm
