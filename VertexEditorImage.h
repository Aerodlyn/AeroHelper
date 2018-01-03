#ifndef VERTEXEDITORIMAGE_H
#define VERTEXEDITORIMAGE_H

#include <QImage>
#include <QPainter>
#include <QWidget>

class VertexEditorImage : public QWidget
{
    Q_OBJECT

    public:
        VertexEditorImage (QWidget *parent = nullptr);
        ~VertexEditorImage ();

    public slots:
        void testSlot ();

    protected:
        void paintEvent (QPaintEvent *event);

    private:
        QImage *image;
};

#endif // VERTEXEDITORIMAGE_H
