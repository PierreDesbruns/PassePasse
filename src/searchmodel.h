// Copyright (C) 2025 Pierre Desbruns
// SPDX-License-Identifier: LGPL-3.0-only

#ifndef SEARCHBARMODEL_H
#define SEARCHBARMODEL_H

#include <QAbstractListModel>
#include <QStringList>
#include <QDebug>

#include "entrymanager.h"


namespace pwm {

class SearchModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit SearchModel(EntryManager* entryManager, QObject* parent = nullptr);
    /**
     * @brief Return number entry names without duplicates.
     */
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    /**
     * @brief Return entry name corresponding to given index.
     */
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

private slots:
    /**
     * @brief Update entry names from entry manager and removes duplicates.
     */
    void updateEntrynames();

private:
    EntryManager* entryManager;
    QStringList entrynames; // without duplicates
};

} // namespace pwm

#endif // SEARCHBARMODEL_H
