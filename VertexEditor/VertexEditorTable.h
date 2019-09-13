#ifndef VERTEX_EDITOR_TABLE_H
#define VERTEX_EDITOR_TABLE_H

#include <QHeaderView>
#include <QLabel>
#include <QResizeEvent>
#include <QString>
#include <QStringList>
#include <QTableWidget>
#include <QVector>
#include <QVectorIterator>

#define INITIAL_NUM_COLUMNS 2
#define INITIAL_NUM_ROWS    0

namespace Aerodlyn
{
    /**
     *
     */
    class VertexEditorTable : public QTableWidget
    {
        public: // Constructors/Deconstructors
            VertexEditorTable (QWidget *parent = nullptr);
            ~VertexEditorTable () override;

        public: // Methods
            void setAssociatedPointList (QVector <float> *pointList = nullptr);

            /**
             * Updates the table, either by updating the last row (i.e. a new data point as been
             *  added) or the entire table (a new point list has been set).
             *
             * @param refresh - True if the entire table must be updated, false otherwise
             */
            void update (const bool refresh = false);

            /**
             * Updates a specific row in the table to reflect new information.
             *
             * @param row - The row to update
             */
            void update (const int row);

        protected: // Methods
            void resizeEvent (QResizeEvent *event) override final;

        private: // Variables
            const QString   DATA_COLUMN_01_HEADER   = "X",
                            DATA_COLUMN_02_HEADER   = "Y";
            QVector <float> *pointList              = nullptr;
    };
}

#endif // VERTEX_EDITOR_TABLE_H
