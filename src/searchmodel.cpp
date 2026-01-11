// Copyright (C) 2026 Pierre Desbruns
// SPDX-License-Identifier: LGPL-3.0-only

#include "searchmodel.h"

namespace pwm {

SearchModel::SearchModel(QObject *parent)
    : QAbstractListModel(parent)
{
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

void SearchModel::updateEntrynames(const QList<Entry>& entryList)
{
    entrynames.clear();

    for (const Entry& entry : entryList)
        entrynames << entry.entryname();

    entrynames.removeDuplicates();

    // Emitting update signal
    QModelIndex topLeft = createIndex(0,0);
    QModelIndex bottomRight = createIndex(rowCount(), 0);
    emit dataChanged(topLeft, bottomRight);
}

} // namespace pwm
