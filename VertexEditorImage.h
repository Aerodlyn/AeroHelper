#ifndef VERTEXEDITORIMAGE_H
#define VERTEXEDITORIMAGE_H

#include <QImage>
#include <QPainter>
#include <QWidget>

/**
 * Designed to be a subcomponent of a VertexEditorWindow instance, this class handles the drawing
 *  of an image as well as the vertex points of a selected data set (given from the owner of this
 *  specific VertexEditorImage instance).
 *
 * @author  Patrick Jahnig (psj516)
 * @version 2018.01.03
 */
class VertexEditorImage : public QWidget
{
    Q_OBJECT

    public:
        /**
         * Creates a new VertexEditorImage instance with the optional QWidget as the parent.
         *
         * @param parent The optional parent of this instance (though VertexEditorImage is designed
         *                  to be used with a VertexEditorWindow instance as a parent).
         */
        VertexEditorImage (QWidget *parent = nullptr);

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
        void paintEvent (QPaintEvent *event) override;

    private:
        QImage *image;

        const QColor BACKGROUND_COLOR = QColor ("#FF19B9");
};

#endif // VERTEXEDITORIMAGE_H
