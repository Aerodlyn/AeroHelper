#ifndef VERTEXEDITORIMAGE_H
#define VERTEXEDITORIMAGE_H

#include <QImage>
#include <QMouseEvent>
#include <QPainter>
#include <QVector>
#include <QWidget>

/**
 * Designed to be a subcomponent of a VertexEditorWindow instance, this class handles the drawing
 *  of an image as well as the vertex points of a selected data set (given from the owner of this
 *  specific VertexEditorImage instance).
 *
 * @author  Patrick Jahnig (psj516)
 * @version 2018.01.13
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
        void mousePressEvent (QMouseEvent *event) override;
        void paintEvent (QPaintEvent *event) override;

    private:
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
};

#endif // VERTEXEDITORIMAGE_H
