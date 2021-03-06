#ifndef VERTEX_EDITOR_RENDERED_IMAGE_H
#define VERTEX_EDITOR_RENDERED_IMAGE_H

#include <functional>
#include <optional>

#include <QImage>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QPolygonF>
#include <QPointF>
#include <QResizeEvent>
#include <QVector>

namespace Aerodlyn
{
    /**
     * A subcomponent of {@link VertexEditorImage}, represents the image file that gets rendered to the
     *  application as well as the background that gets rendered behind that image.
     *
     * @author  Patrick Jahnig (Aerodlyn)
     * @version 2020.01.18
     */
    class VertexEditorRenderedImage : public QLabel
    {
        public: // Constructors/Deconstructors
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
            VertexEditorRenderedImage (const int &selectedPointIndex, QPointF &center);

            /**
             * Destroys this {@link VertexEditorRenderedImage} instance.
             *  NOTE: Most of the memory management is done by Qt. This is here in case it is needed later
             */
            ~VertexEditorRenderedImage () override;

        public: // Methods
            /**
             * Loads the image located at the given filepath and sets it as the image to render.
             *
             * @param filepath  - The (absolute) filepath of the image to load
             *
             * @return True if the image was loaded, false otherwise
             */
            bool load (const QString &filepath);

            /**
             * Resizes this {@link VertexEditorRenderedImage} instance to either the dimensions of the parent
             *  or the image, whichever is larger. The width of this instance may be from the parent while the
             *  height may be from the image, or vice versa.
             *
             * @param size  - The size of the resized parent widget
             */
            void resizeToFit (const QSize &size);

            /**
             * Sets the region to use for input handling and rendering.
             *
             * @param region - The {@link QPolygonF} region of points
             */
            void setRegion (std::optional <std::reference_wrapper <QPolygonF>> region);

        protected: // Methods
            /**
             * See: https://doc.qt.io/qt-5/qwidget.html#paintEvent
             */
            void paintEvent (QPaintEvent *event) override final;

        private: // Variables
            const int                                          &selectedPointIndex;

            const double                                       POINT_RADIUS         = 5.0;

            const QColor                                       BACKGROUND_COLOR     = QColor ("#FF00FF");

            QImage                                             image;

            QPointF                                            &center;


            std::optional <std::reference_wrapper <QPolygonF>> region;
    };
}

#endif // VERTEX_EDITOR_RENDERED_IMAGE_H
