#ifndef VERTEXEDITORIMAGE_H
#define VERTEXEDITORIMAGE_H

#include <QCursor>
#include <QImage>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QPoint>
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
     * @author  Patrick Jahnig (psj516)
     * @version 2018.07.15
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
            ~VertexEditorImage ();

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
             * Sets the point list to use for input handling and rendering.
             *
             * @param pointList - The pointer to the selected list of points, can be null
             */
            void setPointList (QVector <float> *pointList);

            /**
             * Returns the mouse position associated with the given {@link QMouseEvent} adjusted for the location
             *  of the viewport.
             *
             * @param event - The QMouseEvent to get the mouse coordinates from
             *
             * @return The adjusted mouse position as a {@link QPoint} object
             */
            const QPoint adjustedMousePosition (const QMouseEvent * const event);

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
             * See: https://doc.qt.io/qt-5/qwidget.html#resizeEvent
             */
            void resizeEvent (QResizeEvent *event) override final;

        private: // Variables
            int                         hoveredPointIndex = -1;

            const float                 POINT_RADIUS = 5.0f;

            QPoint                      center;
            QVector <float>             *pointList;
            VertexEditorRenderedImage   *image;

            const QWidget               PARENT;

        signals:
            /**
             * Signals that the mouse has been clicked within this VertexEditorImage instance, and
             *  passes the location of that click to the slot that is connected to this method.
             *
             * @param x - The x coordinate of the mouse click
             * @param y - The y coordinate of the mouse click
             */
            void mouseClicked (float x, float y);

            /**
             * Signals that the mouse has been moved within this VertexEditorImage instance, and
             *  may be hovering over a data point. If so then index is the index of that point,
             *  else index is -1.
             *
             * @param index - The index of the point being hovered over, else if no such point exists,
             *                  -1.
             */
            void mouseHovered (int index);
    };
}

#endif // VERTEXEDITORIMAGE_H
