#include "VertexEditorTable.h"

/* Constructors/Deconstructors */
Aerodlyn::VertexEditorTable::VertexEditorTable (QWidget *parent) : QTableWidget (INITIAL_NUM_ROWS, INITIAL_NUM_COLUMNS, parent)
{
    QStringList headerList;
    headerList.append (DATA_COLUMN_01_HEADER);
    headerList.append (DATA_COLUMN_02_HEADER);

    setAlternatingRowColors (true);
    setHorizontalHeaderLabels (headerList);
}

Aerodlyn::VertexEditorTable::~VertexEditorTable () {}

/* Public Methods */
void Aerodlyn::VertexEditorTable::setRegion (std::optional <std::reference_wrapper <QPolygonF>> region)
{
    this->clearContents ();
    this->region = region;

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
    if (!region.has_value ())
        return;

    int index = refresh ? 0 : rowCount ();
    setRowCount (region->get ().length ());

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
    if (!region.has_value ())
        return;

    const QPointF point = region->get ().at (row);

    setCellWidget (row, 0, new QLabel (QString::number (point.x ())));
    setCellWidget (row, 1, new QLabel (QString::number (point.y ())));
}

/* Overridden Protected Methods */
void Aerodlyn::VertexEditorTable::resizeEvent (QResizeEvent *event)
{
    int columnWidth = static_cast <int> (event->size ().width () * 0.5f);

    setColumnWidth (0, columnWidth);
    setColumnWidth (1, columnWidth);
}
