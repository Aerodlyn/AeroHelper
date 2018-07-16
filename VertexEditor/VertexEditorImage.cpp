#include "VertexEditorImage.h"

/**
 * Designed to be a subcomponent of a VertexEditorWindow instance, this class handles the drawing
 *  of an image as well as the vertex points of a selected data set (given from the owner of this
 *  specific VertexEditorImage instance).
 *
 * @author  Patrick Jahnig (psj516)
 * @version 2018.07.15
 */

/* Constructors/Deconstructors */
/**
 * Creates a new VertexEditorImage instance with the optional QWidget as the parent.
 *
 * @param parent    - The optional parent of this instance (though VertexEditorImage is
 *                      designed to be used with a VertexEditorWindow instance as a parent).
 */
Aerodlyn::VertexEditorImage::VertexEditorImage (QWidget *parent) : QScrollArea (parent), PARENT (parent)
{
    image = new VertexEditorRenderedImage (hoveredPointIndex, center);

    setMinimumWidth (300);
    setMouseTracking (true);
    setWidget (image);
}

/**
 * Destroys this {@link VertexEditorImage} instance.
 *  NOTE: Most of the memory management is done by Qt. This is here in case it is needed later
 */
Aerodlyn::VertexEditorImage::~VertexEditorImage () {}

/* Public Methods */
/**
 * Sets the image that is drawn to the one contained within the file at the given filepath.
 *
 * @param filepath The (full) filepath of the image file to set the image to draw
 *
 * @return True if the image was loaded and set, false otherwise
 */
bool Aerodlyn::VertexEditorImage::setImageFile (const QString &filepath) { return image->load (filepath); }

/**
 * Sets the point list to use for input handling and rendering.
 *
 * @param pointList - The pointer to the selected list of points, can be null
 */
void Aerodlyn::VertexEditorImage::setPointList (QVector <float> *pointList)
{
    this->pointList = pointList;
    image->setPointList (this->pointList);
}

/**
 * Returns the mouse position associated with the given {@link QMouseEvent} adjusted for the location
 *  of the viewport.
 *
 * @param event - The QMouseEvent to get the mouse coordinates from
 *
 * @return The adjusted mouse position as a {@link QPoint} object
 */
const QPoint Aerodlyn::VertexEditorImage::adjustedMousePosition (const QMouseEvent * const event)
{
    const int evtX = (event->x () + horizontalScrollBar()->value ()) - center.x (),
              evtY = (event->y () + verticalScrollBar ()->value ()) - center.y ();

    return QPoint (evtX, evtY);
}

/* Protected Methods */
/**
 * See: https://doc.qt.io/qt-5/qwidget.html#mouseMoveEvent
 */
void Aerodlyn::VertexEditorImage::mouseMoveEvent (QMouseEvent *event)
{
    if (!pointList)
        return;

    const QPoint adjPos = adjustedMousePosition (event);

    hoveredPointIndex = -1;
    for (int i = 0; i < pointList->size () && hoveredPointIndex == -1; i += 2)
    {
        const float x = pointList->at (i), y = pointList->at (i + 1);
        if (Utils::isInCircle (adjPos.x (), adjPos.y (), x, y, POINT_RADIUS))
            hoveredPointIndex = i / 2;
    }

    emit mouseHovered (hoveredPointIndex);
    image->update ();
}

/**
 * See: https://doc.qt.io/qt-5/qwidget.html#mousePressEvent
 */
void Aerodlyn::VertexEditorImage::mousePressEvent (QMouseEvent *event)
{
    const QPoint adjPos = adjustedMousePosition (event);

    // TODO: Look into handling floating points
    emit mouseClicked (adjPos.x (), adjPos.y ());
    mouseMoveEvent (event);

    image->update ();
}

/**
 * See: https://doc.qt.io/qt-5/qwidget.html#resizeEvent
 */
void Aerodlyn::VertexEditorImage::resizeEvent (QResizeEvent *event) { image->resizeToFit (event->size ()); }
