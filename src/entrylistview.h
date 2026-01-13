// Copyright (C) 2026 Pierre Desbruns
// SPDX-License-Identifier: LGPL-3.0-only

#ifndef ENTRYLISTVIEW_H
#define ENTRYLISTVIEW_H

#include <QListView>

#include "entry.h"


namespace pwm {

class EntryListView : public QListView
{
    Q_OBJECT

public:
    EntryListView(QWidget* parent = nullptr);

signals:
    /**
     * @brief Emitted when given entry is selected.
     */
    void entrySelected(const Entry& entry);
};

} // namespace pwm

#endif // ENTRYLISTVIEW_H
