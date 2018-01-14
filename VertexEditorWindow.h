#ifndef VERTEXEDITORWINDOW_H
#define VERTEXEDITORWINDOW_H

#include <algorithm>

#include <QDir>
#include <QFileDialog>
#include <QGridLayout>
#include <QInputDialog>
#include <QList>
#include <QListWidget>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QPushButton>
#include <QString>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QVector>

#include "Utils.h"
#include "VertexEditorImage.h"

/**
 * Represents the original version of AeroHelper.
 *
 * This class creates a window that allows the user to use an image (i.e. a sprite) to
 *  create arrays of floating points for collision bounds or any other form of data that
 *  requires an array of points to create polygonal shapes.
 *
 * @author  Patrick Jahnig (Aerodlyn)
 * @version 2018.01.13
 */
class VertexEditorWindow : public QMainWindow
{
    Q_OBJECT

    public:
        /**
         * Creates the VertexEditorWindow with the optional QWidget as its parent.
         *
         * @param parent The parent of the VertexEditorWindow
         */
        VertexEditorWindow (QWidget *parent = nullptr);

        /**
         * Destroys the VertexEditorWindow.
         *  NOTE: Most of the memory management is done by Qt.
         *  NOTE: This is here in case I need it in the future, but it does nothing at the moment.
         */
        ~VertexEditorWindow ();

    private:
        int selectedDataSetIndex;

        const unsigned int MARGIN = 5, SPACING = 5;

        QAction                     *loadImageAction, *saveDataAction;
        QGridLayout                 *gridLayout;
        QList <QString>             dataSetList;
        QListWidget                 *dataSetListWidget;
        QMenu                       *fileMenu;
        QPushButton                 *addDataSetButton, *clearDataSetButton, *clearAllDataSetsButton,
                                        *deleteDataSet, *deleteAllDataSets;
        QString                     lastOpenedDirPath = QDir::homePath ();
        QTableWidget                *selectedDataSetTable;
        QVBoxLayout                 *dataSetVBox;
        QVector <float>             currentDataSetPoints;
        QVector <QVector <float>>   dataSets;
        QWidget                     *centralWidget;

        VertexEditorImage *vertexImage;

        const QString DATA_COLUMN_01_HEADER         = "X", DATA_COLUMN_02_HEADER = "Y";
        const QString DATA_SET_INPUT_DIALOG_HEADER  = "Enter name of data set",
                        DATA_SET_INPUT_DIALOG_DESC  = "A data set name can contain any character except for spaces"
                                                        "\nas any will be removed upon creation. Multiple data sets"
                                                        "\ncan be created by separating the names with a semicolon"
                                                        " (';').";
        const QString FILE_INPUT_HEADER             = "Open Image",
                        FILE_INPUT_FILE_TYPES       = "Images (*jpeg *jpg *.png)";
        const QString WINDOW_TITLE                  = "Vertex Editor | Ver. 2018.01.07";

    private slots:
        /**
         * Adds the given coordinates to the currently selected data set.
         *  NOTE: Does nothing if no data set is selected.
         *
         * @param x The x coordinate
         * @param y The y coordinate
         */
        void addPointToSelectedDataSet (const float x, const float y);

        /**
         * Handles attempting to add a new data set. Prompts the user to enter the name of the new set,
         *  and then inserts into the sorted data list. Does nothing if canceled, and won't add the data
         *  set if one already has the same name.
         */
        void handleAddDataSet ();

        /**
         * Handles selected a row (data set) from the list widget that contains the names of all of
         *  the data sets.
         *
         * @param currentRow The row (index) of the data set that was selected
         */
        void handleDataSelection (int currentRow);

        /**
         * Handles opening a new image that the user can base their clicks upon. Replaces the previously
         *  opened image if one was previously opened.
         */
        void handleOpenImage ();

        /**
         * Handles saving the current data sets to file, whose filetype is of the users choosing (possibly
         *  defined by the user). Does nothing if no data sets exist.
         */
        void handleSaveDataSets ();
};

#endif
