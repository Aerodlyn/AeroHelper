#include "ColorListDelegate.h"

/**
 * This class handles opening a color picker dialog when editting a palette option as well as
 *   painting a black border around the color display in the list of colors that make up the
 *   palette.
 *
 * @author  Patrick Jahnig (Aerodlyn)
 * @version 2020.02.19
 */

/* Public overridden methods */
bool Aerodlyn::ColorListDelegate::editorEvent (
    QEvent *event,
    QAbstractItemModel *model,
    const QStyleOptionViewItem &option,
    const QModelIndex &index
)
{
    Q_UNUSED (option);

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
    QStyledItemDelegate::paint (painter, option, index);

    painter->drawRect (option.rect.x () + 5, option.rect.y () + 2, 15, 15);
}
