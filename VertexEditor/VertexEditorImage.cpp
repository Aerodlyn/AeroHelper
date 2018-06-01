#include "VertexEditorImage.h"

/**
 * Designed to be a subcomponent of a VertexEditorWindow instance, this class handles the drawing
 *  of an image as well as the vertex points of a selected data set (given from the owner of this
 *  specific VertexEditorImage instance).
 *
 * @author  Patrick Jahnig (psj516)
 * @version 2018.05.31
 */

/**
 * Creates a new VertexEditorImage instance with the optional QWidget as the parent.
 *
 * @param parent    The optional parent of this instance (though VertexEditorImage is
 *                      designed to be used with a VertexEditorWindow instance as a parent).
 * @param pointList This represents the currently selected list of data points that this
 *                      VertexEditorImage instance should draw
 */
Aerodlyn::VertexEditorImage::VertexEditorImage (QWidget *parent, const QVector <float> &pointList)
    : QWidget (parent), POINTS_LIST (pointList), PARENT (parent)
{
    image = new QImage ();

    setMinimumWidth (300);
    setMouseTracking (true);
}

/**
 * Destroys the VertexEditorImage.
 *  NOTE: Most of the memory management is done by Qt.
 */
Aerodlyn::VertexEditorImage::~VertexEditorImage () { delete image; }

/**
 * Sets the image that is drawn to the one contained within the file at the given filepath.
 *
 * @param filepath The (full) filepath of the image file to set the image to draw
 */
void Aerodlyn::VertexEditorImage::setImageFile (QString &filepath)
{
    image->load (filepath);
    update ();
}

/* Protected Methods */
void Aerodlyn::VertexEditorImage::mouseMoveEvent (QMouseEvent *event)
{
    if (!image->isNull ())
    {
        hoveredPointIndex = -1;
        for (int i = 0; i < POINTS_LIST.size (); i += 2)
        {
            const float x = POINTS_LIST.at (i), y = POINTS_LIST.at (i + 1);
            if (Utils::isInCircle (event->x (), event->y (), x, y, POINT_RADIUS))
            {
                hoveredPointIndex = i / 2;
                break;
            }
        }

        emit mouseHovered (hoveredPointIndex);
        update ();
    }
}

void Aerodlyn::VertexEditorImage::mousePressEvent (QMouseEvent *event)
{
    if (!image->isNull ())
    {
        // TODO: Look into handling floating points
        emit mouseClicked (event->x (), event->y ());
        mouseMoveEvent (event);

        update ();
    }
}

void Aerodlyn::VertexEditorImage::paintEvent (QPaintEvent *event)
{
    Q_UNUSED (event);

    int size = POINTS_LIST.size ();
    QPainter painter (this);

    painter.setPen (BACKGROUND_COLOR);
    painter.setBrush (QBrush (painter.pen ().color ()));
    painter.drawRect (0, 0, width () - 1, height () - 1);
    painter.drawImage ((width () - image->width ()) / 2, (height () - image->height ()) / 2, *image);
    painter.setPen (QColor ("#FFFFFF"));

    if (size >= 6)
        painter.drawLine (POINTS_LIST.at (0), POINTS_LIST.at (1), POINTS_LIST.at (size - 2), POINTS_LIST.at (size - 1));

    for (int i = 0; i < size; i += 2)
    {
        float x = POINTS_LIST.at (i), y = POINTS_LIST.at (i + 1);

        if (size >= 4 && i < size - 2)
            painter.drawLine (x, y, POINTS_LIST.at (i + 2), POINTS_LIST.at (i + 3));

        if (hoveredPointIndex * 2 == i)
            painter.setBrush (QBrush ("#000000"));

        else
            painter.setBrush (QBrush ("#FFFFFF"));

        painter.drawEllipse (x - POINT_RADIUS / 2.0f, y - POINT_RADIUS / 2.0f, POINT_RADIUS, POINT_RADIUS);
    }
}
