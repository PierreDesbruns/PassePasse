// Copyright (C) 2025 Pierre Desbruns
// SPDX-License-Identifier: LGPL-3.0-only

#ifndef ENTRYLISTMODEL_H
#define ENTRYLISTMODEL_H

#include <QAbstractListModel>
#include <QVariant>
#include <QDebug>

#include "entrymanager.h"


namespace pwm {

class EntryListModel : public QAbstractListModel
{
public:
    explicit EntryListModel(EntryManager* entryManager, QObject* parent = nullptr);
    /**
     * @brief Return number entries from entry manager's list.
     */
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    /**
     * @brief Return index's entryname or username depending on role.
     * @param index: Index corresponding to the entry.
     * @param role: DisplayRole or UserRole.
     * @return entryname if Displayrole; username if UserRole.
     */
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

public slots:
    /**
     * @brief Emit datachanged signal.
     */
    void updateData();

private:
    EntryManager* entryManager;
};

} // namespace pwm

#endif // ENTRYLISTMODEL_H
