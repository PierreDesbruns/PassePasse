// Copyright (C) 2025 Pierre Desbruns
// SPDX-License-Identifier: LGPL-3.0-only

#include "entrylistview.h"

namespace pwm {

EntryListView::EntryListView(EntryListModel* entryListModel, QWidget* parent)
    : QListView{parent}
{
    setModel(entryListModel);
    setItemDelegate(new EntryListDelegate(this));

    connect(this, SIGNAL(pressed(QModelIndex)), this, SLOT(triggerEntrySelected(QModelIndex)));
}

void EntryListView::triggerEntrySelected(const QModelIndex& index)
{
    emit entrySelected(index.data(Qt::DisplayRole).toString(), index.data(Qt::UserRole).toString());
}

} // namespace pwm
