// Copyright (C) 2026 Pierre Desbruns
// SPDX-License-Identifier: LGPL-3.0-only

#include "entrylistdelegate.h"

namespace pwm {

EntryListDelegate::EntryListDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{
}

void EntryListDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    // Highlight item if selected
    if(option.state & QStyle::State_HasFocus)
        painter->fillRect(option.rect, option.palette.color(QPalette::Highlight));

    // Font
    QFont font = painter->font();

    // Entry info
    QString entryname = index.data().value<Entry>().entryname();
    QString username = index.data().value<Entry>().username();
    QString date = index.data().value<Entry>().date();
    QPixmap pixmap = iconFromDate(date).pixmap(QSize(40,40));

    // Rectangles
    QRect iconRect(option.rect.left(), option.rect.top(), 40, option.rect.height());
    QRect entrynameRect = option.rect.adjusted(40,0,0,-20);
    QRect usernameRect = option.rect.adjusted(40,20,0,0);

    painter->save();

    // Drawing icon
    painter->drawPixmap(iconRect.adjusted(12,12,-12,-12), pixmap);

    // Drawing entry name
    font.setBold(true);
    painter->setFont(font);
    painter->drawText(entrynameRect, Qt::AlignBottom|Qt::AlignLeft|Qt::TextWordWrap, entryname);

    // Drawing user name
    font.setBold(false);
    painter->setFont(font);
    painter->setPen(QColor(100,100,100));
    painter->drawText(usernameRect, Qt::AlignTop|Qt::AlignLeft|Qt::TextWordWrap, username);

    painter->restore();
}

QSize EntryListDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    return QSize(option.rect.width(), 40);
}

QIcon iconFromDate(const QString& date)
{
    QDate pwdDate = QDate::fromString(date, "yyyy.MM.dd");
    QDate currentDate = QDate::currentDate();
    int monthDifference = 0; // number of months separating [currentDate] from [pwdDate]

    if (pwdDate.isNull())
    {
        // Date format is incorrect
        qWarning() << "Date format of " << date << "is incorrect. Date icon will not appear.";
        return QIcon();
    }

    monthDifference = (currentDate.year() - pwdDate.year()) * 12 + (currentDate.month() - pwdDate.month());

    if (monthDifference < 3) return QIcon(":/green");
    if (monthDifference < 6) return QIcon(":/orange");
    return QIcon(":/red");
}

} // namepsace pwm
