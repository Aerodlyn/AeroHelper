#ifndef COLOR_LIST_DELEGATE_H
#define COLOR_LIST_DELEGATE_H

#include <QAbstractItemModel>
#include <QApplication>
#include <QColor>
#include <QColorDialog>
#include <QEvent>
#include <QModelIndex>
#include <QPainter>
#include <QRect>
#include <QStyle>
#include <QStyledItemDelegate>
#include <QStyleOptionButton>
#include <QStyleOptionViewItem>

#include "ColorConverter/Utilities/Color.h"

namespace Aerodlyn
{
   /**
    * This class handles opening a color picker dialog when editting a palette option as well as
    *   painting a black border around the color display in the list of colors that make up the
    *   palette.
    *
    * @author  Patrick Jahnig (Aerodlyn)
    * @version 2020.02.19
    */
    class ColorListDelegate : public QStyledItemDelegate
    {
        public: // Overridden methods
            bool editorEvent (
                QEvent *event,
                QAbstractItemModel *model,
                const QStyleOptionViewItem &option,
                const QModelIndex &index
            ) override;

            void paint (QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    };
}

#endif
