#include "VertexEditorImage.h"

#include <iostream>

VertexEditorImage::VertexEditorImage (QWidget *parent) : QWidget (parent)
{
    image = new QImage ();

    setMinimumWidth (300);
}

VertexEditorImage::~VertexEditorImage () { delete image; }

void VertexEditorImage::testSlot () { std::cout << "Hello!\n"; }

/* Protected Methods */
void VertexEditorImage::paintEvent (QPaintEvent *event)
{
    Q_UNUSED (event);

    QPainter painter (this);

    painter.setPen (QColor ("#FF19B9"));
    painter.setBrush (QBrush (painter.pen ().color ()));
    painter.drawRect (0, 0, width () - 1, height () - 1);
    painter.drawImage ((width () - image->width ()) / 2, (height () - image->height ()) / 2, *image);
}
