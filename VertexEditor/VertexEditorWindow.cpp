#include "VertexEditorWindow.h"

/**
 * Represents the original version of AeroHelper.
 *
 * This class creates a window that allows the user to use an image (i.e. a sprite) to
 *  create arrays of floating points for collision bounds or any other form of data that
 *  requires an array of points to create polygonal shapes.
 *
 * @author  Patrick Jahnig (Aerodlyn)
 * @version 2018.05.31
 */

/**
 * Creates the VertexEditorWindow with the optional QWidget as its parent.
 *
 * @param parent The parent of the VertexEditorWindow
 */
Aerodlyn::VertexEditorWindow::VertexEditorWindow (QWidget *parent) : QMainWindow (parent), selectedDataSetIndex (-1)
{
    // Or perhaps this
    centralWidget = new QWidget ();
    setCentralWidget (centralWidget);

    // This might be the issue on Linux
    fileMenu = menuBar ()->addMenu ("&File");

    QList <QKeySequence> loadShortcuts = QList <QKeySequence> ();
    loadShortcuts.append (QKeySequence ("Ctrl+L"));
    loadShortcuts.append (QKeySequence ("Cmd+L"));

    loadImageAction = new QAction ("&Load Image");
    loadImageAction->setShortcuts (loadShortcuts);
    fileMenu->addAction (loadImageAction);
    connect (loadImageAction, &QAction::triggered, this, &VertexEditorWindow::handleOpenImage);

    QList <QKeySequence> saveShortcuts = QList <QKeySequence> ();
    saveShortcuts.append (QKeySequence ("Ctrl+S"));
    saveShortcuts.append (QKeySequence ("Cmd+S"));

    saveDataAction = new QAction ("Save Data Sets");
    saveDataAction->setShortcuts (saveShortcuts);
    fileMenu->addAction (saveDataAction);
    connect (saveDataAction, &QAction::triggered, this, &VertexEditorWindow::handleSaveDataSets);

    QList <QKeySequence> quitShortcuts = QList <QKeySequence> ();
    quitShortcuts.append (QKeySequence ("Ctrl+Q"));
    quitShortcuts.append (QKeySequence ("Cmd+Q"));

    quitAction = new QAction ("&Quit");
    quitAction->setShortcuts (quitShortcuts);
    fileMenu->addAction (quitAction);
    connect (quitAction, &QAction::triggered, this, &VertexEditorWindow::handleQuit);

    gridLayout = new QGridLayout ();
    gridLayout->setMargin (MARGIN);
    gridLayout->setSpacing (SPACING);
    gridLayout->setColumnStretch (0, 2);
    gridLayout->setColumnMinimumWidth (1, 275);

    dataSetVBox = new QVBoxLayout ();

    addDataSetButton = new QPushButton ("Add New Data Set");
    dataSetVBox->addWidget (addDataSetButton);
    connect (addDataSetButton, &QPushButton::released, this, &VertexEditorWindow::handleAddDataSet);

    clearDataSetButton = new QPushButton ("Clear Selected Data Set");
    dataSetVBox->addWidget (clearDataSetButton);
    connect (clearDataSetButton, &QPushButton::released, this, &VertexEditorWindow::handleClearDataSet);

    clearAllDataSetsButton = new QPushButton ("Clear All Data Sets");
    dataSetVBox->addWidget (clearAllDataSetsButton);
    connect (clearAllDataSetsButton, &QPushButton::released, this, &VertexEditorWindow::handleClearAllDataSets);

    deleteDataSet = new QPushButton ("Delete Selected Data Set");
    dataSetVBox->addWidget (deleteDataSet);

    deleteAllDataSets = new QPushButton ("Delete All Data Sets");
    dataSetVBox->addWidget (deleteAllDataSets);

    gridLayout->addLayout (dataSetVBox, 0, 1);

    dataSetListWidget = new QListWidget ();
    gridLayout->addWidget (dataSetListWidget, 1, 1);
    connect (dataSetListWidget, &QListWidget::currentRowChanged, this, &VertexEditorWindow::handleDataSelection);

    vertexTable = new Aerodlyn::VertexEditorTable ();
    gridLayout->addWidget (vertexTable, 2, 1);

    vertexImage = new Aerodlyn::VertexEditorImage (this);
    gridLayout->addWidget (vertexImage, 0, 0, gridLayout->rowCount (), 1);
    connect (vertexImage, &Aerodlyn::VertexEditorImage::mouseClicked, this,
             &Aerodlyn::VertexEditorWindow::addPointToSelectedDataSet);
    connect (vertexImage, &Aerodlyn::VertexEditorImage::mouseHovered, this,
             &Aerodlyn::VertexEditorWindow::handleHoveredPoint);
    connect (vertexImage, &Aerodlyn::VertexEditorImage::mouseMoved, this,
             &Aerodlyn::VertexEditorWindow::handleMouseMoved);

    centralWidget->setLayout (gridLayout);
    resize (minimumSize ());
    setWindowTitle (WINDOW_TITLE);
}

/**
 * Destroys the VertexEditorWindow.
 *  NOTE: Most of the memory management is done by Qt.
 *  NOTE: This is here in case I need it in the future, but it does nothing at the moment.
 */
Aerodlyn::VertexEditorWindow::~VertexEditorWindow () {}

/* Private slots */
/**
 * Adds the given coordinates to the currently selected data set.
 *  NOTE: Does nothing if no data set is selected.
 *
 * @param x The x coordinate
 * @param y The y coordinate
 */
void Aerodlyn::VertexEditorWindow::addPointToSelectedDataSet (const float x, const float y)
{
    if (dataSetListWidget->selectedItems ().size () > 0)
    {
        currentDataSetPoints->append (x);
        currentDataSetPoints->append (y);

        // *(dataSets.data () + selectedDataSetIndex) = currentDataSetPoints;
        vertexTable->update ();
    }
}

/**
 * Handles attempting to add a new data set. Prompts the user to enter the name of the new set,
 *  and then inserts into the sorted data list. Does nothing if canceled, and won't add the data
 *  set if one already has the same name.
 */
void Aerodlyn::VertexEditorWindow::handleAddDataSet ()
{
    bool confirmed;
    QStringList names = QInputDialog::getText (this, DATA_SET_INPUT_DIALOG_HEADER, DATA_SET_INPUT_DIALOG_DESC,
        QLineEdit::Normal, "", &confirmed)
        .simplified ()
        .replace (" ", "")
        .split (";", QString::SkipEmptyParts);

    if (confirmed)
    {
        for (QString s : names)
        {
            if (!dataSetList.contains (s))
            {
                dataSetList.append (s);
                std::sort (dataSetList.begin (), dataSetList.end ());

                int index = dataSetList.indexOf (s);

                dataSetListWidget->insertItem (index, s);
                dataSets.insert (index, QVector <float> ());
            }

            else
            {
                // Prompt user if they would like to rename one of the conflicting data sets
                QString errorText = QString ("A data set with the name '%1' already exists."
                    "\nYou can either clear that data set, or delete it and add it again.").arg (s);
                QMessageBox::critical (this, "Error", errorText);
            }
        }
    }
}

/**
 * Handles clearing the currently selected data set. Does nothing if no data set is selected.
 */
void Aerodlyn::VertexEditorWindow::handleClearDataSet ()
{
    if (selectedDataSetIndex != -1)
    {
        currentDataSetPoints->clear ();
        // *(dataSets.data () + selectedDataSetIndex) = currentDataSetPoints;

        vertexImage->update ();
        vertexTable->update ();
    }
}

/**
 * Handles clearing all currently existing data sets. Does nothing if no data sets exist.
 */
void Aerodlyn::VertexEditorWindow::handleClearAllDataSets ()
{
    for (int i = 0; i < dataSets.size (); i++)
        (dataSets.data () + i)->clear ();

    if (selectedDataSetIndex != -1)
    {
        currentDataSetPoints->clear ();

        vertexImage->update ();
        vertexTable->update ();
    }
}

/**
 * Handles selecting a row (data set) from the list widget that contains the names of all of
 *  the data sets.
 *
 * @param currentRow The row (index) of the data set that was selected
 */
void Aerodlyn::VertexEditorWindow::handleDataSelection (int currentRow)
{
    selectedDataSetIndex = currentRow;
    currentDataSetPoints = dataSets.data () + currentRow;

    vertexTable->setAssociatedPointList (currentDataSetPoints);
    vertexImage->setPointList (currentDataSetPoints);
    vertexImage->update ();
}

/**
 * Handles selecting the row of the table view that represents the point that the user is currently
 *  hovering their mouse over. If the user is not hovering over a point, then the last added point is
 *  highlighted in the table view.
 *
 * @param index - The index of the point that the mouse is hovering over, or -1 if no such point exists
 */
void Aerodlyn::VertexEditorWindow::handleHoveredPoint (int index)
{
    if (index != -1)
        vertexTable->selectRow (index);

    else
        vertexTable->selectRow (vertexTable->rowCount () - 1);
}

/**
 * Handles moving a hovered point as the user clicks and drags.
 *
 * @param x     - The x coordinate of the mouse click
 * @param y     - The y coordinate of the mouse click
 * @param index - The index of the point being hovered over
 */
void Aerodlyn::VertexEditorWindow::handleMouseMoved (const float x, const float y, const int index)
{
    int adjIndex = index * 2;
    currentDataSetPoints->data () [adjIndex] = x;
    currentDataSetPoints->data () [adjIndex + 1] = y;

    vertexTable->update (index);
}

/**
 * Handles opening a new image that the user can base their clicks upon. Replaces the previously
 *  opened image if one was previously opened.
 */
void Aerodlyn::VertexEditorWindow::handleOpenImage ()
{
    QString filepath = QFileDialog::getOpenFileName (this, FILE_INPUT_HEADER, lastOpenedDirPath,
        FILE_INPUT_FILE_TYPES);

    if (!filepath.isEmpty ())
    {
        lastOpenedDirPath = filepath.left (filepath.lastIndexOf (QDir::separator ()));
        vertexImage->setImageFile (filepath);
    }
}

/**
 * Handles gracefully exiting the program. If the user has unsaved data, a prompt will
 *  inform the user of that and ask if they want to save the data before exiting.
 */
void Aerodlyn::VertexEditorWindow::handleQuit () { exit (0); }

/**
 * Handles saving the current data sets to file, whose filetype is of the users choosing (possibly
 *  defined by the user). Does nothing if no data sets exist.
 */
void Aerodlyn::VertexEditorWindow::handleSaveDataSets ()
{
    if (dataSetList.length () > 0)
        QString filename = QFileDialog::getSaveFileName (this, "Save Data Sets", lastOpenedDirPath);
}
