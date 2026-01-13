// Copyright (C) 2026 Pierre Desbruns
// SPDX-License-Identifier: LGPL-3.0-only

#include "entrylistmodel.h"

namespace pwm {

EntryListModel::EntryListModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

int EntryListModel::rowCount(const QModelIndex& /*parent*/) const
{
    return (filterString.isEmpty() ? entries.size() : entriesFiltered.size());
}

QVariant EntryListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= entries.size())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return QVariant::fromValue<Entry>(filterString.isEmpty()
                                              ? entries.at(index.row())
                                              : entriesFiltered.at(index.row()));

    return QVariant();
}

void EntryListModel::filter(const QString& entryName)
{
    if (entryName.isEmpty())
        return;

    for (const Entry& entry : entries)
    {
        if (entry.entryname() == entryName)
            entriesFiltered << entry;
    }

    filterString = entryName;

    // Emitting update signal
    QModelIndex topLeft = createIndex(0,0);
    QModelIndex bottomRight = createIndex(rowCount(), 0);
    emit dataChanged(topLeft, bottomRight);
}

void EntryListModel::clearFilter()
{
    filterString.clear();
    entriesFiltered.clear();

    // Emitting update signal
    QModelIndex topLeft = createIndex(0,0);
    QModelIndex bottomRight = createIndex(rowCount(), 0);
    emit dataChanged(topLeft, bottomRight);
}

void EntryListModel::updateEntries(const QList<Entry>& entryList)
{
    entries = entryList;

    clearFilter();

    // Emitting update signal
    QModelIndex topLeft = createIndex(0,0);
    QModelIndex bottomRight = createIndex(rowCount(), 0);
    emit dataChanged(topLeft, bottomRight);
}

} // namespace pwm
