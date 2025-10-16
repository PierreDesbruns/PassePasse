// Copyright (C) 2025 Pierre Desbruns
// SPDX-License-Identifier: LGPL-3.0-only

#include "entrylistmodel.h"

namespace pwm {

EntryListModel::EntryListModel(EntryManager* entryManager, QObject *parent)
    : QAbstractListModel{parent}, entryManager(entryManager)
{

}

int EntryListModel::rowCount(const QModelIndex& /*parent*/) const
{
    return entryManager->entryList().size();
}

QVariant EntryListModel::data(const QModelIndex& index, int /*role*/) const
{
    QVariant data;

    if (index.isValid())
    {
        if (index.row() < entryManager->entryList().size())
            data.setValue(entryManager->entryList().at(index.row()));
    }

    return data;
}

void EntryListModel::updateData()
{
    // Creating index and emitting update signal
    QModelIndex topLeft = createIndex(0,0);
    QModelIndex bottomRight = createIndex(rowCount(), 0);
    emit dataChanged(topLeft, bottomRight);
}

} // namespace pwm
