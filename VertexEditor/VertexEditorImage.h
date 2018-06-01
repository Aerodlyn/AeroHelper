#ifndef VERTEXEDITORIMAGE_H
#define VERTEXEDITORIMAGE_H

#include <iostream>

#include <QCursor>
#include <QImage>
#include <QMouseEvent>
#include <QPainter>
#include <QPoint>
#include <QVector>
#include <QWidget>

#include "Root/Utils.h"

namespace Aerodlyn
{
    /**
     * Designed to be a subcomponent of a VertexEditorWindow instance, this class handles the drawing
     *  of an image as well as the vertex points of a selected data set (given from the owner of this
     *  specific VertexEditorImage instance).
     *
     * @author  Patrick Jahnig (psj516)
     * @version 2018.05.31
     */
    class VertexEditorImage : public QWidget
    {
        Q_OBJECT

        public:
            /**
             * Creates a new VertexEditorImage instance with the optional QWidget as the parent.
             *
             * @param parent    The optional parent of this instance (though VertexEditorImage is
             *                      designed to be used with a VertexEditorWindow instance as a parent).
             * @param pointList This represents the currently selected list of data points that this
             *                      VertexEditorImage instance should draw
             */
            VertexEditorImage (QWidget *parent = nullptr, const QVector <float> &pointList = QVector <float> ());

            /**
             * Destroys the VertexEditorImage.
             *  NOTE: Most of the memory management is done by Qt.
             */
            ~VertexEditorImage ();

            /**
             * Sets the image that is drawn to the one contained within the file at the given filepath.
             *
             * @param filepath The (full) filepath of the image file to set the image to draw
             */
            void setImageFile (QString &filepath);

        protected:
            void mouseMoveEvent (QMouseEvent *event) override final;
            void mousePressEvent (QMouseEvent *event) override final;
            void paintEvent (QPaintEvent *event) override final;

        private:
            const float POINT_RADIUS = 5.0f;

            int hoveredPointIndex = -1;

            QImage *image;

            const QColor            BACKGROUND_COLOR = QColor ("#FF19B9");
            const QVector <float>   &POINTS_LIST;

            const QWidget PARENT;

        signals:
            /**
             * Signals that the mouse has been clicked within this VertexEditorImage instance, and
             *  passes the location of that click to the slot that is connected to this method.
             *
             * @param x The x coordinate of the mouse click
             * @param y The y coordinate of the mouse click
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

#endif
