#include "VertexEditorWindow.h"

/**
 * Represents the original version of AeroHelper.
 *
 * This class creates a window that allows the user to use an image (i.e. a sprite) to
 *  create arrays of floating points for collision bounds or any other form of data that
 *  requires an array of points to create polygonal shapes.
 *
 * @author  Patrick Jahnig (Aerodlyn)
 * @version 2020.01.18
 */

/* Constructors/Deconstructors */
/**
 * Creates the VertexEditorWindow with the optional QWidget as its parent.
 *
 * @param parent The parent of the VertexEditorWindow
 */
Aerodlyn::VertexEditorWindow::VertexEditorWindow (QWidget *parent) : QMainWindow (parent), selectedDataSetIndex (-1)
{
    centralWidget = new QWidget ();
    setCentralWidget (centralWidget);

    gridLayout = new QGridLayout ();
    gridLayout->setMargin (static_cast <int> (MARGIN));
    gridLayout->setSpacing (static_cast <int> (SPACING));
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
    connect (deleteDataSet, &QPushButton::released, this, &VertexEditorWindow::handleDeleteDataSet);

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

    // Create menu bar
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

    // Set minimum size and set it as the initial size
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
void Aerodlyn::VertexEditorWindow::addPointToSelectedDataSet (const double x, const double y)
{
    if (currentRegion.has_value ())
    {
        currentRegion->get () << QPointF (x, y);
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
    // TODO: Adjust to use regex
    bool confirmed;
    QStringList names = QInputDialog::getText (this, DATA_SET_INPUT_DIALOG_HEADER, DATA_SET_INPUT_DIALOG_DESC,
        QLineEdit::Normal, "", &confirmed)
        .simplified ()
        .replace (" ", "")
        .split (";", QString::SkipEmptyParts);

    if (confirmed)
    {
        for (QString name : names)
        {
            const int index = dataSets.add (name);

            if (index >= 0)
                dataSetListWidget->insertItem (index, name);

            else
            {
                // Prompt user if they would like to rename one of the conflicting data sets
                QString errorText = QString ("A data set with the name '%1' already exists."
                    "\nYou can either clear that data set, or delete it and add it again.").arg (name);
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
    if (currentRegion.has_value ())
    {
        currentRegion->get ().clear ();

        vertexImage->update ();
        vertexTable->update ();
    }
}

/**
 * Handles clearing all currently existing data sets. Does nothing if no data sets exist.
 */
void Aerodlyn::VertexEditorWindow::handleClearAllDataSets ()
{
    for (int i = 0; i < dataSetListWidget->count (); i++)
    {
        const auto item = dataSets.get (dataSetListWidget->item (i)->text ());
        if (item.has_value ())
            item->get ().clear ();

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
    currentRegion = dataSets.get (dataSetListWidget->item (selectedDataSetIndex)->text ());

    vertexTable->setRegion (currentRegion);
    vertexImage->setRegion (currentRegion);
    vertexImage->update ();
}

/**
 * Handles deleting the currently selected data set. Does nothing if no data set is
 *  selected.
 */
void Aerodlyn::VertexEditorWindow::handleDeleteDataSet ()
{
    if (currentRegion.has_value ())
    {
        const QListWidgetItem *item = dataSetListWidget->takeItem (selectedDataSetIndex);

        dataSets.remove (item->text ());

        delete item;
        currentRegion = std::nullopt; // TODO: Set to another existing region if there is one

        vertexTable->setRegion (currentRegion);
    }
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
void Aerodlyn::VertexEditorWindow::handleMouseMoved (const double x, const double y, const int index)
{
    if (!currentRegion.has_value ())
        return;

    QPointF &point = currentRegion->get () [index];

    point.setX (x);
    point.setY (y);

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
void Aerodlyn::VertexEditorWindow::handleQuit ()
    { exit (0); }

/**
 * Handles saving the current data sets to file, whose filetype is of the users choosing (possibly
 *  defined by the user). Does nothing if no data sets exist.
 */
void Aerodlyn::VertexEditorWindow::handleSaveDataSets ()
{
    /* if (dataSetList.length () > 0)
        QString filename = QFileDialog::getSaveFileName (this, "Save Data Sets", lastOpenedDirPath); */
}
