#include "VertexEditor/VertexEditorRenderedImage.h"

#include <iostream>

// Public Methods
Aerodlyn::VertexEditorRenderedImage::VertexEditorRenderedImage (int &hoveredPointIndex, QPoint &center, const QVector <float> &pointsList)
    : QLabel (nullptr), hoveredPointIndex (hoveredPointIndex), center (center), POINTS_LIST (pointsList)
{
    setSizePolicy (QSizePolicy::Ignored, QSizePolicy::Ignored);
    setScaledContents (true);
    setMouseTracking (true);
}

Aerodlyn::VertexEditorRenderedImage::~VertexEditorRenderedImage () {}

bool Aerodlyn::VertexEditorRenderedImage::load (const QString &filepath)
{
    if (image.load (filepath))
    {
        resizeToFit (size ());
        update ();

        return true;
    }

    return false;
}

void Aerodlyn::VertexEditorRenderedImage::resizeEvent (QResizeEvent *event) { resizeToFit (event->size ()); }

// Protected Methods
void Aerodlyn::VertexEditorRenderedImage::paintEvent (QPaintEvent *event)
{
    Q_UNUSED (event);

    QPainter painter (this);
    int size = POINTS_LIST.size ();

    painter.setPen (BACKGROUND_COLOR);
    painter.setBrush (QBrush (painter.pen ().color ()));
    painter.drawRect (0, 0, width () - 1, height () - 1);
    painter.drawImage ((width () - image.width ()) / 2, (height () - image.height ()) / 2, image);

    painter.setPen (QColor ("#FFFFFF"));
    if (size >= 6)
        painter.drawLine (POINTS_LIST.at (0) + center.x (), POINTS_LIST.at (1) + center.y (),
                          POINTS_LIST.at (size - 2) + center.x (), POINTS_LIST.at (size - 1) + center.y ());

    for (int i = 0; i < size; i += 2)
    {
        const float x = POINTS_LIST.at (i) + center.x (),
                    y = POINTS_LIST.at (i + 1) + center.y ();

        if (size >= 4 && i < size - 2)
            painter.drawLine (x, y, POINTS_LIST.at (i + 2) + center.x (), POINTS_LIST.at (i + 3) + center.y ());

        if (hoveredPointIndex * 2 == i)
            painter.setBrush (QBrush ("#000000"));

        else
            painter.setBrush (QBrush ("#FFFFFF"));

        painter.drawEllipse (x - POINT_RADIUS / 2.0f, y - POINT_RADIUS / 2.0f, POINT_RADIUS, POINT_RADIUS);
    }
}

// Private Methods
void Aerodlyn::VertexEditorRenderedImage::resizeToFit (const QSize &size)
{
    if (image.isNull ())
        setFixedSize (size);

    else
    {
        int iHeight = image.height (),
            iWidth  = image.width (),
            sHeight = size.height (),
            sWidth  = size.width ();

        setFixedSize (iWidth > sWidth ? iWidth : sWidth, iHeight > sHeight ? iHeight : sHeight);
    }

    center = QPoint (width () / 2, height () / 2);
}
