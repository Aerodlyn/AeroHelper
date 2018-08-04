#include "VertexEditorTable.h"

Aerodlyn::VertexEditorTable::VertexEditorTable (QWidget *parent) : QTableWidget (INITIAL_NUM_ROWS, INITIAL_NUM_COLUMNS, parent)
{
    QStringList headerList;
    headerList.append (DATA_COLUMN_01_HEADER);
    headerList.append (DATA_COLUMN_02_HEADER);

    setAlternatingRowColors (true);
    setHorizontalHeaderLabels (headerList);

    horizontalHeader ()->setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
    horizontalHeader ()->setSectionResizeMode (QHeaderView::Fixed);
}

Aerodlyn::VertexEditorTable::~VertexEditorTable () {}

void Aerodlyn::VertexEditorTable::resizeEvent (QResizeEvent *event)
{
    int columnWidth = event->size ().width () * 0.5;

    setColumnWidth (0, columnWidth);
    setColumnWidth (1, columnWidth + 5);
}

void Aerodlyn::VertexEditorTable::setAssociatedPointList (QVector <float> *pointList)
{
    this->clearContents ();
    this->pointList = pointList;

    update (true);
}

/**
 * Updates the table, either by updating the last row (i.e. a new data point as been
 *  added) or the entire table (a new point list has been set).
 *
 * @param refresh - True if the entire table must be updated, false otherwise
 */
void Aerodlyn::VertexEditorTable::update (const bool refresh)
{
    if (!pointList)
        return;

    int index = refresh ? 0 : rowCount ();
    setRowCount (pointList->size () / 2);

    for (; index < rowCount (); index++)
        update (index);
}

/**
 * Updates a specific row in the table to reflect new information.
 *
 * @param row - The row to update
 */
void Aerodlyn::VertexEditorTable::update (const int row)
{
    if (!pointList)
        return;

    setCellWidget (row, 0, new QLabel (QString::number (this->pointList->at (row * 2))));
    setCellWidget (row, 1, new QLabel (QString::number (this->pointList->at ((row * 2) + 1))));
}
