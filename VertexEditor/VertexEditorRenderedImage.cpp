#include "VertexEditor/VertexEditorRenderedImage.h"

/**
 * A subcomponent of {@link VertexEditorImage}, represents the image file that gets rendered to the
 *  application as well as the background that gets rendered behind that image.
 *
 * @author  Patrick Jahnig (Aerodlyn)
 * @version 2020.01.18
 */

/* Constructors/Deconstructors */
/**
 * Creates a new {@link VertexEditorRenderedImage} instance, with the given references. These
 *  references are designed to be contained within the parent {@link VertexEditorImage} instance.
 *
 * @param selectedPointIndex    - The integer representing the index of the point that the user has
 *                                  selected
 * @param center                - The current center of the rendered area, used for determining the
 *                                  location to render points by relative to that center (as some
 *                                  coordinates may be negative)
 */
Aerodlyn::VertexEditorRenderedImage::VertexEditorRenderedImage (const int &selectedPointIndex, QPointF &center)
    : QLabel (nullptr), selectedPointIndex (selectedPointIndex), center (center)
{
    setSizePolicy (QSizePolicy::Ignored, QSizePolicy::Ignored);
    setScaledContents (true);
    setMouseTracking (true);
}

/**
 * Destroys this {@link VertexEditorRenderedImage} instance.
 *  NOTE: Most of the memory management is done by Qt. This is here in case it is needed later
 */
Aerodlyn::VertexEditorRenderedImage::~VertexEditorRenderedImage () {}

/* Public Methods */
/**
 * Loads the image located at the given filepath and sets it as the image to render.
 *
 * @param filepath  - The (absolute) filepath of the image to load
 *
 * @return True if the image was loaded, false otherwise
 */
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

/**
 * Resizes this {@link VertexEditorRenderedImage} instance to either the dimensions of the parent
 *  or the image, whichever is larger. The width of this instance may be from the parent while the
 *  height may be from the image, or vice versa.
 *
 * @param size  - The size of the resized parent widget
 */
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

    center = QPointF (width () / 2, height () / 2);
}

/**
 * Sets the point list to use for input handling and rendering.
 *
 * @param pointList - The pointer to the selected list of points, can be null
 */
void Aerodlyn::VertexEditorRenderedImage::setRegion (std::optional <std::reference_wrapper <QPolygonF>> region)
    { this->region = region; }

/* Overridden Protected Methods */
/**
 * See: https://doc.qt.io/qt-5/qwidget.html#paintEvent
 */
void Aerodlyn::VertexEditorRenderedImage::paintEvent (QPaintEvent *event)
{
    Q_UNUSED (event)

    QPainter painter (this);
    painter.setPen (BACKGROUND_COLOR);
    painter.setBrush (QBrush (painter.pen ().color ()));
    painter.drawRect (0, 0, width () - 1, height () - 1);
    painter.drawImage ((width () - image.width ()) / 2, (height () - image.height ()) / 2, image);

    if (!region.has_value ())
        return;

    int size = region->get ().size ();

    painter.setPen (QColor ("#FFFFFF"));
    if (size >= 2)
        painter.drawLine (region->get ().at (0) + center, region->get ().at (size - 1) + center);

    for (int i = 0; i < size; i++)
    {
        const QPointF point = region->get ().at (i) + center;

        if (size >= 2 && i < size - 1)
            painter.drawLine (point, region->get ().at (i + 1) + center);

        if (selectedPointIndex == i)
            painter.setBrush (QBrush ("#000000"));

        else
            painter.setBrush (QBrush ("#FFFFFF"));

        painter.drawEllipse (point, POINT_RADIUS, POINT_RADIUS);
    }
}
