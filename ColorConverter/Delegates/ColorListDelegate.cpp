#include "ColorListDelegate.h"

/**
 * This class handles opening a color picker dialog when editting a palette option as well as
 *   painting a black border around the color display in the list of colors that make up the
 *   palette.
 *
 * @author  Patrick Jahnig (Aerodlyn)
 * @version 2020.02.23
 */

/* Public overridden methods */
bool Aerodlyn::ColorListDelegate::editorEvent (
    QEvent *event,
    QAbstractItemModel *model,
    const QStyleOptionViewItem &option,
    const QModelIndex &index
)
{
    Q_UNUSED (option)

    if (event->type () == QEvent::MouseButtonDblClick)
    {
        const QColor currentColor = model->data (index, Qt::DecorationRole).value <QColor> ();
        const QColor editedColor = QColorDialog::getColor (currentColor);

        if (editedColor.isValid ())
        {
            int r, g, b, a;
            editedColor.getRgb (&r, &g, &b, &a);

            model->setData (index, QVariant::fromValue (Color (r, g, b, a)));
        }

        return true;
    }

    return false;
}

void Aerodlyn::ColorListDelegate::paint (QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (option.state & QStyle::State_Selected)
        painter->fillRect (option.rect, option.palette.highlight ());

    const QColor color = index.data (Qt::DecorationRole).value <QColor> ();
    const QString text = index.data ().toString ();

    const QRect colorRect = QRect (option.rect.x () + 1, option.rect.y () + 1, option.rect.height () - 2, option.rect.height () - 2);
    painter->fillRect (colorRect, Qt::black);
    painter->fillRect (colorRect.adjusted (1, 1, -1, -1), color);

    painter->drawText (colorRect.x () + colorRect.width () + 5, option.rect.y (), option.rect.width (), option.rect.height (), Qt::AlignVCenter, text);
}
