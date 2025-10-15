// Copyright (C) 2025 Pierre Desbruns
// SPDX-License-Identifier: LGPL-3.0-only

#ifndef ENTRYLISTVIEW_H
#define ENTRYLISTVIEW_H

#include <QListView>
#include <QString>

#include "entrylistmodel.h"
#include "entrylistdelegate.h"
#include "entrymanager.h"


namespace pwm {

class EntryListView : public QListView
{
    Q_OBJECT

public:
    EntryListView(EntryListModel* entryListModel, EntryManager* entryManager, QWidget* parent = nullptr);

public slots:
    /**
     * @brief Trigger entrySelected signal when an index is selected.
     */
    void triggerEntrySelected(const QModelIndex& index);

signals:
    /**
     * @brief Emitted when an entry is selected.
     * @param entryname, username: Entry and user names of selected entry.
     */
    void entrySelected(const Entry& entry);

private:
    EntryManager* entryManager;
};

} // namespace pwm

#endif // ENTRYLISTVIEW_H
