#ifndef VERTEXEDITORTABLE_H
#define VERTEXEDITORTABLE_H

#include <QHeaderView>
#include <QLabel>
#include <QResizeEvent>
#include <QString>
#include <QStringList>
#include <QTableWidget>
#include <QVector>
#include <QVectorIterator>

namespace Aerodlyn
{
    class VertexEditorTable : public QTableWidget
    {
        Q_OBJECT

        public:
            VertexEditorTable (QWidget *parent = nullptr);
            ~VertexEditorTable ();

            void resizeEvent (QResizeEvent *event) override final;

            void setAssociatedPointList (QVector <float> *pointList);
            void update ();

        private:
            const QString   DATA_COLUMN_01_HEADER   = "X",
                            DATA_COLUMN_02_HEADER   = "Y";
            QVector <float> *pointList              = nullptr;
    };
}

#endif
