#ifndef VERTEX_EDITOR_RENDERED_IMAGE_H
#define VERTEX_EDITOR_RENDERED_IMAGE_H

#include <QImage>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QResizeEvent>
#include <QVector>

namespace Aerodlyn
{
    class VertexEditorRenderedImage : public QLabel
    {
        public:
            VertexEditorRenderedImage (int &hoveredPointIndex, QPoint &center, const QVector <float> &pointsList);

            ~VertexEditorRenderedImage ();

            bool load (const QString &filepath);

            void resizeEvent (QResizeEvent *event) override final;

        protected:
            void paintEvent (QPaintEvent *event) override final;

        private:
            int                     &hoveredPointIndex;

            const float             POINT_RADIUS = 5.0f;

            QImage                  image;
            QPoint                  &center;

            const QColor            BACKGROUND_COLOR = QColor ("#FF19B9");
            const QVector <float>   &POINTS_LIST;

            void resizeToFit (const QSize &size);
    };
}

#endif // VERTEX_EDITOR_RENDERED_IMAGE_H
