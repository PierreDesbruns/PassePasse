// Copyright (C) 2025 Pierre Desbruns
// SPDX-License-Identifier: LGPL-3.0-only

#include "entrylistview.h"

namespace pwm {

EntryListView::EntryListView(QWidget* parent)
    : QListView{parent}
{
    connect(
        this, &QListView::pressed,
        this, [this](const QModelIndex& index) { emit entrySelected(index.data().value<Entry>()); }
    );
}

} // namespace pwm
