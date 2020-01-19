#include "VertexEditorImage.h"

/**
 * Designed to be a subcomponent of a VertexEditorWindow instance, this class handles user input
 *  related to a drawn image.
 *
 * @author  Patrick Jahnig (psj516)
 * @version 2020.01.18
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
    image = new VertexEditorRenderedImage (selectedPointIndex, center);

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
bool Aerodlyn::VertexEditorImage::setImageFile (const QString &filepath)
    { return image->load (filepath); }

/**
 * Sets the region to use for input handling and rendering.
 *
 * @param region - The {@link QPolygonF} region of points
 */
void Aerodlyn::VertexEditorImage::setRegion (std::optional <std::reference_wrapper <QPolygonF>> region)
{
    this->region = region;
    image->setRegion (this->region);
}

void Aerodlyn::VertexEditorImage::update ()
    { image->update (); }

/**
 * Returns the mouse position associated with the given {@link QMouseEvent} adjusted for the location
 *  of the viewport.
 *
 * @param event - The QMouseEvent to get the mouse coordinates from
 *
 * @return The adjusted mouse position as a {@link QPointF} object
 */
const QPointF Aerodlyn::VertexEditorImage::adjustedMousePosition (const QMouseEvent * const event) const
{
    const double evtX = (event->x () + horizontalScrollBar()->value ()) - center.x ();
    const double evtY = (event->y () + verticalScrollBar ()->value ()) - center.y ();

    return QPointF (evtX, evtY);
}

/* Overridden Protected Methods */
/**
 * See: https://doc.qt.io/qt-5/qwidget.html#mouseMoveEvent
 */
void Aerodlyn::VertexEditorImage::mouseMoveEvent (QMouseEvent *event)
{
    if (!region.has_value ())
        return;

    const QPointF adjPos = adjustedMousePosition (event);
    if (!leftButtonHeld)
    {
        selectedPointIndex = -1;
        for (int i = 0; i < region->get ().size () && selectedPointIndex == -1; i++)
        {
            const QPointF point = region->get ().at (i);
            if (Utils::isInCircle (adjPos, point, POINT_RADIUS))
                selectedPointIndex = i;
        }
    }

    // TODO: Selected point index to prevent losing the point being dragged
    if (selectedPointIndex != -1)
    {
        emit mouseHovered (selectedPointIndex);

        if (leftButtonHeld)
            emit mouseMoved (adjPos.x (), adjPos.y (), selectedPointIndex);
    }

    image->update ();
}

/**
 * See: https://doc.qt.io/qt-5/qwidget.html#mousePressEvent
 */
void Aerodlyn::VertexEditorImage::mousePressEvent (QMouseEvent *event)
{
    const QPointF adjPos = adjustedMousePosition (event);
    leftButtonHeld = true;

    if (selectedPointIndex == -1)
        emit mouseClicked (adjPos.x (), adjPos.y ());

    image->update ();
}

/**
 * See: https://doc.qt.io/qt-5/qwidget.html#mouseReleaseEvent
 */
void Aerodlyn::VertexEditorImage::mouseReleaseEvent (QMouseEvent *event)
{
    Q_UNUSED (event)
    leftButtonHeld = false;
}

/**
 * See: https://doc.qt.io/qt-5/qwidget.html#resizeEvent
 */
void Aerodlyn::VertexEditorImage::resizeEvent (QResizeEvent * const event)
    { image->resizeToFit (event->size ()); }
