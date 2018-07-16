#include "VertexEditor/VertexEditorRenderedImage.h"

/* Constructors/Deconstructors */
/**
 * Creates a new {@link VertexEditorRenderedImage} instance, with the given references. These references
 *  are designed to be contained within the parent {@link VertexEditorImage} instance.
 *
 * @param hoveredPointIndex - The integer representing the index of the point that the user is currently
 *                              hovering over
 * @param center            - The current center of the rendered area, used for determining the location
 *                              to render points by relative to that center (as some coordinates may be
 *                              negative)
 */
Aerodlyn::VertexEditorRenderedImage::VertexEditorRenderedImage (int &hoveredPointIndex, QPoint &center)
    : QLabel (nullptr), hoveredPointIndex (hoveredPointIndex), center (center)
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

    center = QPoint (width () / 2, height () / 2);
}

/**
 * Sets the point list to use for input handling and rendering.
 *
 * @param pointList - The pointer to the selected list of points, can be null
 */
void Aerodlyn::VertexEditorRenderedImage::setPointList (QVector <float> *pointList) { this->pointList = pointList; }

/* Protected Methods */
/**
 * See: https://doc.qt.io/qt-5/qwidget.html#paintEvent
 */
void Aerodlyn::VertexEditorRenderedImage::paintEvent (QPaintEvent *event)
{
    Q_UNUSED (event);

    QPainter painter (this);
    painter.setPen (BACKGROUND_COLOR);
    painter.setBrush (QBrush (painter.pen ().color ()));
    painter.drawRect (0, 0, width () - 1, height () - 1);
    painter.drawImage ((width () - image.width ()) / 2, (height () - image.height ()) / 2, image);

    if (!pointList)
        return;

    int size = pointList->size ();

    painter.setPen (QColor ("#FFFFFF"));
    if (size >= 6)
        painter.drawLine (pointList->at (0) + center.x (), pointList->at (1) + center.y (),
                          pointList->at (size - 2) + center.x (), pointList->at (size - 1) + center.y ());

    for (int i = 0; i < size; i += 2)
    {
        const float x = pointList->at (i) + center.x (),
                    y = pointList->at (i + 1) + center.y ();

        if (size >= 4 && i < size - 2)
            painter.drawLine (x, y, pointList->at (i + 2) + center.x (), pointList->at (i + 3) + center.y ());

        if (hoveredPointIndex * 2 == i)
            painter.setBrush (QBrush ("#000000"));

        else
            painter.setBrush (QBrush ("#FFFFFF"));

        painter.drawEllipse (x - POINT_RADIUS / 2.0f, y - POINT_RADIUS / 2.0f, POINT_RADIUS, POINT_RADIUS);
    }
}
