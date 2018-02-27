#include "VertexEditorImage.h"

/**
 * Designed to be a subcomponent of a VertexEditorWindow instance, this class handles the drawing
 *  of an image as well as the vertex points of a selected data set (given from the owner of this
 *  specific VertexEditorImage instance).
 *
 * @author  Patrick Jahnig (psj516)
 * @version 2018.01.14
 */

/**
 * Creates a new VertexEditorImage instance with the optional QWidget as the parent.
 *
 * @param parent    The optional parent of this instance (though VertexEditorImage is
 *                      designed to be used with a VertexEditorWindow instance as a parent).
 * @param pointList This represents the currently selected list of data points that this
 *                      VertexEditorImage instance should draw
 */
VertexEditorImage::VertexEditorImage (QWidget *parent, const QVector <float> &pointList)
    : QWidget (parent), POINTS_LIST (pointList), PARENT (parent)
{
    image = new QImage ();

    setMinimumWidth (300);
}

/**
 * Destroys the VertexEditorImage.
 *  NOTE: Most of the memory management is done by Qt.
 */
VertexEditorImage::~VertexEditorImage () { delete image; }

/**
 * Sets the image that is drawn to the one contained within the file at the given filepath.
 *
 * @param filepath The (full) filepath of the image file to set the image to draw
 */
void VertexEditorImage::setImageFile (QString &filepath)
{
    image->load (filepath);
    update ();
}

/* Protected Methods */
void VertexEditorImage::mousePressEvent (QMouseEvent *event)
{
    if (!image->isNull ())
    {
        // Look into handling floating points
        emit mouseClicked (event->x (), event->y ());
        update ();
    }
}

void VertexEditorImage::paintEvent (QPaintEvent *event)
{
    Q_UNUSED (event);

    QPainter painter (this);

    painter.setPen (BACKGROUND_COLOR);
    painter.setBrush (QBrush (painter.pen ().color ()));
    painter.drawRect (0, 0, width () - 1, height () - 1);
    painter.drawImage ((width () - image->width ()) / 2, (height () - image->height ()) / 2, *image);

    painter.setPen (QColor ("#000000"));
    painter.setBrush (QBrush ("#FFFFFF"));

    for (int i = 0; i < POINTS_LIST.size (); i += 2)
        painter.drawEllipse (POINTS_LIST.at (i), POINTS_LIST.at (i + 1), 5, 5);
}
