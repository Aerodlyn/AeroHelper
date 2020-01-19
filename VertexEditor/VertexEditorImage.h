#ifndef VERTEXEDITORIMAGE_H
#define VERTEXEDITORIMAGE_H

#include <functional>
#include <optional>

#include <QCursor>
#include <QImage>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QPointF>
#include <QPolygonF>
#include <QResizeEvent>
#include <QScrollArea>
#include <QScrollBar>
#include <QVector>
#include <QWidget>

#include "Root/Utils.h"
#include "VertexEditor/VertexEditorRenderedImage.h"

namespace Aerodlyn
{
    /**
     * Designed to be a subcomponent of a VertexEditorWindow instance, this class handles the drawing
     *  of an image as well as the vertex points of a selected data set (given from the owner of this
     *  specific VertexEditorImage instance).
     *
     * @author  Patrick Jahnig (Aerodlyn)
     * @version 2020.01.18
     */
    class VertexEditorImage : public QScrollArea
    {
        Q_OBJECT

        public: // Constructors/Deconstructors
            /**
             * Creates a new VertexEditorImage instance with the optional QWidget as the parent.
             *
             * @param parent    - The optional parent of this instance (though VertexEditorImage is
             *                      designed to be used with a VertexEditorWindow instance as a parent).
             */
            VertexEditorImage (QWidget *parent = nullptr);

            /**
             * Destroys this {@link VertexEditorImage} instance.
             *  NOTE: Most of the memory management is done by Qt. This is here in case it is needed later
             */
            ~VertexEditorImage () override;

        public: // Methods
            /**
             * Sets the image that is drawn to the one contained within the file at the given filepath.
             *
             * @param filepath  - The (full) filepath of the image file to set the image to draw
             *
             * @return True if the image was loaded and set, false otherwise
             */
            bool setImageFile (const QString &filepath);

            /**
             * Sets the region to use for input handling and rendering.
             *
             * @param region - The {@link QPolygonF} region of points
             */
            void setRegion (std::optional <std::reference_wrapper <QPolygonF>> region);

            void update ();

            /**
             * Returns the mouse position associated with the given {@link QMouseEvent} adjusted for the location
             *  of the viewport.
             *
             * @param event - The QMouseEvent to get the mouse coordinates from
             *
             * @return The adjusted mouse position as a {@link QPointF} object
             */
            const QPointF adjustedMousePosition (const QMouseEvent * const event) const;

        protected: // Methods
            /**
             * See: https://doc.qt.io/qt-5/qwidget.html#mouseMoveEvent
             */
            void mouseMoveEvent (QMouseEvent *event) override final;

            /**
             * See: https://doc.qt.io/qt-5/qwidget.html#mousePressEvent
             */
            void mousePressEvent (QMouseEvent *event) override final;

            /**
             * See: https://doc.qt.io/qt-5/qwidget.html#mouseReleaseEvent
             */
            void mouseReleaseEvent (QMouseEvent *event) override final;

            /**
             * See: https://doc.qt.io/qt-5/qwidget.html#resizeEvent
             */
            void resizeEvent (QResizeEvent * event) override final;

        private: // Variables
            bool                                               leftButtonHeld;

            int                                                selectedPointIndex = -1;

            const double                                       POINT_RADIUS       = 5.0;

            QPointF                                            center;

            const QWidget                                      PARENT;

            std::optional <std::reference_wrapper <QPolygonF>> region;

            VertexEditorRenderedImage                          *image;

        signals:
            /**
             * Signals that the mouse has been clicked within this VertexEditorImage instance, and
             *  passes the location of that click to the slot that is connected to this method.
             *
             * @param x - The x coordinate of the mouse click
             * @param y - The y coordinate of the mouse click
             */
            void mouseClicked (const double x, const double y);

            /**
             * Signals that the mouse has been moved within this VertexEditorImage instance, and
             *  may be hovering over a data point. If so then index is the index of that point,
             *  else index is -1.
             *
             * @param index - The index of the point being hovered over, else if no such point exists,
             *                  -1.
             */
            void mouseHovered (const int index);

            /**
             * Signals that the mouse is hovering a point and clicks, and drags.
             *
             * @param x     - The x coordinate of the mouse click
             * @param y     - The y coordinate of the mouse click
             * @param index - The index of the point being hovered over
             */
            void mouseMoved (const double x, const double y, const int index);
    };
}

#endif // VERTEXEDITORIMAGE_H
