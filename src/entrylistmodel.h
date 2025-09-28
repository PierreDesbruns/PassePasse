// Copyright (C) 2025 Pierre Desbruns
// SPDX-License-Identifier: LGPL-3.0-only

#ifndef ENTRYLISTMODEL_H
#define ENTRYLISTMODEL_H

#include <QAbstractListModel>
#include <QStringList>
#include <QVariant>
#include <QDebug>


namespace pwm {

class EntryListModel : public QAbstractListModel
{
public:
    explicit EntryListModel(QObject* parent = nullptr);
    /**
     * @brief Return number of strings in [entrynames].
     * @note Return -1 if [entrynames] and [usernames] have different size.
     */
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    /**
     * @brief Return index's entryname or username, depending on the role.
     */
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    /**
     * @brief Set entry names and user names to given lists.
     */
    void setLists(const QStringList& newEntrynames, const QStringList& newUsernames);

private:
    QStringList entrynames;
    QStringList usernames;
};

} // namespace pwm

#endif // ENTRYLISTMODEL_H
