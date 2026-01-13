// Copyright (C) 2026 Pierre Desbruns
// SPDX-License-Identifier: LGPL-3.0-only

#ifndef ENTRYLISTDELEGATE_H
#define ENTRYLISTDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QIcon>

#include "entry.h"


namespace pwm {

class EntryListDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    EntryListDelegate(QObject* parent = nullptr);
    /**
     * @brief Render items with given entry and user names.
     */
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    /**
     * @brief Return same width as view and height of 40.
     */
    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};

/**
 * @brief Return an icon corresponding to an entry's date of creation.
 * @param date: date of creation of the entry. Expected format: "yyyy.MM.dd".
 * @return Green icon if date is okay; Orange icon if date is about to be passed; Red icon otherwise.
 *
 * Red icon: date is passed (more than 6 months);
 * Orange icon: date is about to be passed (bwt. 3 and 6 months);
 * Green icon: date is okay (less than 3 months).
 */
QIcon iconFromDate(const QString& date);

} // namespace pwm

#endif // ENTRYLISTDELEGATE_H
