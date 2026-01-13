// Copyright (C) 2026 Pierre Desbruns
// SPDX-License-Identifier: LGPL-3.0-only

#ifndef ENTRYLISTMODEL_H
#define ENTRYLISTMODEL_H

#include <QAbstractListModel>
#include <QVariant>
#include <QDebug>

#include "entry.h"


namespace pwm {

class EntryListModel : public QAbstractListModel
{
public:
    explicit EntryListModel(QObject* parent = nullptr);
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
     * @brief Filter entries with given entry name.
     */
    void filter(const QString& entryName);
    void clearFilter();
    /**
     * @brief Update entries with given entry list.
     * @note Filter is cleared.
     */
    void updateEntries(const QList<Entry>& entryList);

private:
    QList<Entry> entries;
    QString filterString;
    QList<Entry> entriesFiltered;
};

} // namespace pwm

#endif // ENTRYLISTMODEL_H
