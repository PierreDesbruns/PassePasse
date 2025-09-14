#include "entrylistdelegate.h"


namespace pwm {

EntryListDelegate::EntryListDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{
}

void EntryListDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const
{
    // Highlight item if selected
    if(option.state & QStyle::State_Selected)
        painter->fillRect(option.rect, option.palette.color(QPalette::Highlight));

    // Font
    QFont font = painter->font();

    // Texts
    QString entryname = index.data(Qt::DisplayRole).toString();
    QString username = index.data(Qt::UserRole).toString();

    // Rectangles
    QRect iconRect(option.rect.left(), option.rect.top(), 40, option.rect.height());
    QRect entrynameRect = option.rect;
    entrynameRect.adjust(40,0,0,-20);
    QRect usernameRect = option.rect;
    usernameRect.adjust(40,20,0,0);

    painter->save();

    // Drawing icon
    //    pen.setStyle(Qt::DotLine);
    //    pen.setColor(QColor(255,0,0));
    //    painter->setPen(pen);
    //    painter->drawLine(iconRect.topLeft(),iconRect.topRight());
    //    painter->drawLine(iconRect.topRight(),iconRect.bottomRight());
    //    painter->drawLine(iconRect.bottomLeft(),iconRect.bottomRight());
    //    painter->drawLine(iconRect.topLeft(),iconRect.bottomLeft());
    //    pen.setStyle(Qt::SolidLine);
    //    painter->setPen(pen);
    painter->drawText(iconRect, Qt::AlignCenter, QString("O"));

    // Drawing entry name
    //    r = option.rect.adjusted(50, 0, 0, 0);
    //    pen.setStyle(Qt::DotLine);
    //    pen.setColor(QColor(0,255,0));
    //    painter->setPen(pen);
    //    painter->drawLine(titleRect.topLeft(),titleRect.topRight());
    //    painter->drawLine(titleRect.topRight(),titleRect.bottomRight());
    //    painter->drawLine(titleRect.bottomLeft(),titleRect.bottomRight());
    //    painter->drawLine(titleRect.topLeft(),titleRect.bottomLeft());
    //    pen.setStyle(Qt::SolidLine);
    //    painter->setPen(pen);

    font.setBold(true);
    painter->setFont(font);
    painter->drawText(entrynameRect, Qt::AlignBottom|Qt::AlignLeft|Qt::TextWordWrap, entryname);

    // Drawing user name
    //    r = option.rect.adjusted(50, 0, 0, 0);
    //    pen.setStyle(Qt::DotLine);
    //    pen.setColor(QColor(0,0,255));
    //    painter->setPen(pen);
    //    painter->drawLine(descRect.topLeft(),descRect.topRight());
    //    painter->drawLine(descRect.topRight(),descRect.bottomRight());
    //    painter->drawLine(descRect.bottomLeft(),descRect.bottomRight());
    //    painter->drawLine(descRect.topLeft(),descRect.bottomLeft());
    //    pen.setStyle(Qt::SolidLine);
    //    painter->setPen(pen);

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

} // namepsace pwm
