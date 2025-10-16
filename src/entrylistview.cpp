// Copyright (C) 2025 Pierre Desbruns
// SPDX-License-Identifier: LGPL-3.0-only

#include "entrylistview.h"

namespace pwm {

EntryListView::EntryListView(EntryListModel* entryListModel, EntryManager* entryManager, QWidget* parent)
    : QListView{parent}, entryManager(entryManager)
{
    setModel(entryListModel);
    setItemDelegate(new EntryListDelegate(this));

    connect(this, SIGNAL(pressed(QModelIndex)), this, SLOT(triggerEntrySelected(QModelIndex)));
}

void EntryListView::triggerEntrySelected(const QModelIndex& index)
{
    emit entrySelected(index.data().value<Entry>());
}

} // namespace pwm
