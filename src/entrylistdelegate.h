// Copyright (C) 2025 Pierre Desbruns
// SPDX-License-Identifier: LGPL-3.0-only

#ifndef ENTRYLISTDELEGATE_H
#define ENTRYLISTDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>

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

} // namespace pwm

#endif // ENTRYLISTDELEGATE_H
