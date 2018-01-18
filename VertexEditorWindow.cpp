#include "VertexEditorWindow.h"

/**
 * Represents the original version of AeroHelper.
 *
 * This class creates a window that allows the user to use an image (i.e. a sprite) to
 *  create arrays of floating points for collision bounds or any other form of data that
 *  requires an array of points to create polygonal shapes.
 *
 * @author  Patrick Jahnig (Aerodlyn)
 * @version 2018.01.18
 */

/**
 * Creates the VertexEditorWindow with the optional QWidget as its parent.
 *
 * @param parent The parent of the VertexEditorWindow
 */
VertexEditorWindow::VertexEditorWindow (QWidget *parent) : QMainWindow (parent)
{
    QStringList headerList;
    headerList.append (DATA_COLUMN_01_HEADER);
    headerList.append (DATA_COLUMN_02_HEADER);

    centralWidget = new QWidget ();
    setCentralWidget (centralWidget);

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
    gridLayout->setSpacing(SPACING);
    gridLayout->setColumnStretch(0, 2);

    dataSetVBox = new QVBoxLayout ();

    addDataSetButton = new QPushButton ("Add New Data Set");
    dataSetVBox->addWidget (addDataSetButton);
    connect (addDataSetButton, &QPushButton::released, this, &VertexEditorWindow::handleAddDataSet);

    clearDataSetButton = new QPushButton ("Clear Selected Data Set");
    dataSetVBox->addWidget (clearDataSetButton);

    clearAllDataSetsButton = new QPushButton ("Clear All Data Sets");
    dataSetVBox->addWidget (clearAllDataSetsButton);

    deleteDataSet = new QPushButton ("Delete Selected Data Set");
    dataSetVBox->addWidget (deleteDataSet);

    deleteAllDataSets = new QPushButton ("Delete All Data Sets");
    dataSetVBox->addWidget (deleteAllDataSets);

    gridLayout->addLayout(dataSetVBox, 0, 1);

    dataSetListWidget = new QListWidget ();
    gridLayout->addWidget (dataSetListWidget, 1, 1);
    connect (dataSetListWidget, &QListWidget::currentRowChanged, this, &VertexEditorWindow::handleDataSelection);

    selectedDataSetTable = new QTableWidget (0, 2);
    selectedDataSetTable->setAlternatingRowColors (true);
    selectedDataSetTable->setHorizontalHeaderLabels (headerList);
    gridLayout->addWidget (selectedDataSetTable, 2, 1);

    vertexImage = new VertexEditorImage (this, currentDataSetPoints);
    gridLayout->addWidget (vertexImage, 0, 0, gridLayout->rowCount (), 1);
    connect (vertexImage, &VertexEditorImage::mouseClicked, this, &VertexEditorWindow::addPointToSelectedDataSet);

    centralWidget->setLayout (gridLayout);
    resize (minimumSize ());
    setWindowTitle (WINDOW_TITLE);
}

/**
 * Destroys the VertexEditorWindow.
 *  NOTE: Most of the memory management is done by Qt.
 *  NOTE: This is here in case I need it in the future, but it does nothing at the moment.
 */
VertexEditorWindow::~VertexEditorWindow () {}

/* Private methods */
/**
 * Adds the given coordinates to the data table that represents the data of the currently
 *  selected data set. The data will be added at the given row index.
 *  TODO: Add insert functionality
 *
 * @param x     The x coordinate to add
 * @param y     The y coordinate to add
 * @param index The row index to add the coordinates to
 */
void VertexEditorWindow::addPointToDataTable (const float x, const float y, const int index)
{
    if (selectedDataSetTable->rowCount () <= index)
        selectedDataSetTable->setRowCount (index + 1);

    selectedDataSetTable->setCellWidget (index, 0, new QLabel (QString::number (x)));
    selectedDataSetTable->setCellWidget (index, 1, new QLabel (QString::number (y)));
}

/* Private slots */
/**
 * Adds the given coordinates to the currently selected data set.
 *  NOTE: Does nothing if no data set is selected.
 *
 * @param x The x coordinate
 * @param y The y coordinate
 */
void VertexEditorWindow::addPointToSelectedDataSet (const float x, const float y)
{
    if (dataSetListWidget->selectedItems ().size () > 0)
    {
        currentDataSetPoints.append (x);
        currentDataSetPoints.append (y);

        addPointToDataTable (x, y, currentDataSetPoints.size () / 2 - 1);

        *(dataSets.data () + selectedDataSetIndex) = currentDataSetPoints;
    }
}

/**
 * Handles attempting to add a new data set. Prompts the user to enter the name of the new set,
 *  and then inserts into the sorted data list. Does nothing if canceled, and won't add the data
 *  set if one already has the same name.
 */
void VertexEditorWindow::handleAddDataSet ()
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
 * Handles selected a row (data set) from the list widget that contains the names of all of
 *  the data sets.
 *
 * @param currentRow The row (index) of the data set that was selected
 */
void VertexEditorWindow::handleDataSelection (int currentRow)
{
    selectedDataSetIndex = currentRow;
    currentDataSetPoints = *(dataSets.data () + currentRow);

    selectedDataSetTable->clear ();

    for (int i = 0; i < currentDataSetPoints.size (); i += 2)
        addPointToDataTable (currentDataSetPoints.at (i), currentDataSetPoints.at (i + 1), i / 2);

    vertexImage->update ();
}

/**
 * Handles opening a new image that the user can base their clicks upon. Replaces the previously
 *  opened image if one was previously opened.
 */
void VertexEditorWindow::handleOpenImage ()
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
void VertexEditorWindow::handleQuit () { exit (0); }

/**
 * Handles saving the current data sets to file, whose filetype is of the users choosing (possibly
 *  defined by the user). Does nothing if no data sets exist.
 */
void VertexEditorWindow::handleSaveDataSets ()
{
    if (dataSetList.length () > 0)
        QString filename = QFileDialog::getSaveFileName (this, "Save Data Sets", lastOpenedDirPath);
}
