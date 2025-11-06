// Copyright (C) 2025 Pierre Desbruns
// SPDX-License-Identifier: LGPL-3.0-only

#ifndef ENTRYLISTMODEL_H
#define ENTRYLISTMODEL_H

#include <QAbstractListModel>
#include <QVariant>
#include <QStringList>
#include <QDebug>

#include "entrymanager.h"


namespace pwm {

class EntryListModel : public QAbstractListModel
{
public:
    explicit EntryListModel(EntryManager* entryManager, QObject* parent = nullptr);
    /**
     * @brief Return number entries.
     */
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    /**
     * @brief Return entry corresponding to given index.
     */
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

public slots:
    /**
     * @brief Filter entrynames list with given filter.
     */
    void filter(const QString& filter);
    /**
     * @brief Cancel filter by resetting entrynames list.
     */
    void reset();

private:
    EntryManager* entryManager;
    QList<Entry> entries;
};

} // namespace pwm

#endif // ENTRYLISTMODEL_H
