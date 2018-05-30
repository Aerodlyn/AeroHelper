#include "VertexEditorTable.h"

Aerodlyn::VertexEditorTable::VertexEditorTable (QWidget *parent) : QTableWidget (0, 2, parent)
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
    /*int vertHeaderWidth = verticalHeader ()->width (); */
    int columnWidth = event->size ().width () * 0.5;

    setColumnWidth (0, columnWidth);
    setColumnWidth (1, columnWidth + 5);
}

void Aerodlyn::VertexEditorTable::setAssociatedPointList (QVector <float> *pointList)
{
    this->clearContents ();
    this->pointList = pointList;

    setRowCount (this->pointList->size () / 2);
    for (int i = 0; i < rowCount (); i++)
    {
        setCellWidget (i, 0, new QLabel (QString::number (this->pointList->at (i * 2))));
        setCellWidget (i, 1, new QLabel (QString::number (this->pointList->at ((i * 2) + 1))));
    }
}

void Aerodlyn::VertexEditorTable::update ()
{
    if (!pointList)
        return;

    int oldRowCount = rowCount ();
    setRowCount (pointList->size () / 2);

    for (int i = oldRowCount; i < rowCount (); i++)
    {
        setCellWidget (i, 0, new QLabel (QString::number (this->pointList->at (i * 2))));
        setCellWidget (i, 1, new QLabel (QString::number (this->pointList->at ((i * 2) + 1))));
    }
}
