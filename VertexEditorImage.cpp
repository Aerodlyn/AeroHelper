#include "VertexEditorImage.h"

/**
 * Designed to be a subcomponent of a VertexEditorWindow instance, this class handles the drawing
 *  of an image as well as the vertex points of a selected data set (given from the owner of this
 *  specific VertexEditorImage instance).
 *
 * @author  Patrick Jahnig (psj516)
 * @version 2018.01.03
 */

/**
 * Creates a new VertexEditorImage instance with the optional QWidget as the parent.
 *
 * @param parent The optional parent of this instance (though VertexEditorImage is designed
 *                  to be used with a VertexEditorWindow instance as a parent).
 */
VertexEditorImage::VertexEditorImage (QWidget *parent) : QWidget (parent)
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
void VertexEditorImage::paintEvent (QPaintEvent *event)
{
    Q_UNUSED (event);

    QPainter painter (this);

    painter.setPen (BACKGROUND_COLOR);
    painter.setBrush (QBrush (painter.pen ().color ()));
    painter.drawRect (0, 0, width () - 1, height () - 1);
    painter.drawImage ((width () - image->width ()) / 2, (height () - image->height ()) / 2, *image);
}
