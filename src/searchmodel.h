// Copyright (C) 2026 Pierre Desbruns
// SPDX-License-Identifier: LGPL-3.0-only

#ifndef SEARCHBARMODEL_H
#define SEARCHBARMODEL_H

#include <QAbstractListModel>
#include <QStringList>
#include <QDebug>

#include "entry.h"


namespace pwm {

class SearchModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit SearchModel(QObject* parent = nullptr);
    /**
     * @brief Return number entry names without duplicates.
     */
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    /**
     * @brief Return entry name corresponding to given index.
     */
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

public slots:
    /**
     * @brief Update entry names from given entry list and removes duplicates.
     */
    void updateEntrynames(const QList<Entry>& entryList);

private:
    QStringList entrynames; // without duplicates
};

} // namespace pwm

#endif // SEARCHBARMODEL_H
