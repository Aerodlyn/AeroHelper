#include "ColorConvertWindow.h"
#include "ui_ColorConvertWindow.h"

/**
 * This class handles creating a GUI to facilitate visual interaction with the color_converter
 *  CLI tool.
 *
 * @author  Patrick Jahnig (Aerodlyn)
 * @version 2020.02.19
 */

/**
 * Creates a new ColorConvertWindow instance with the optional parent.
 *
 * @param parent - The QWidget to treat as the parent of this ColorConvertWindow
 *  instance
 */
Aerodlyn::ColorConvertWindow::ColorConvertWindow (QWidget *parent) : QMainWindow (parent)
{
    ui = new Ui::ColorConvertWindow ();
    ui->setupUi (this);

    ui->colorListView->setItemDelegate (&colorListDelegate);
    colorListDelegate.setParent (ui->colorListView);

    ui->colorListView->setModel (&colorListModel);
}

Aerodlyn::ColorConvertWindow::~ColorConvertWindow ()
    { delete ui; }

/* Private slots */
/**
 * Handles adding a new Color instance to the user's stored palette.
 */
void Aerodlyn::ColorConvertWindow::handleAddColor ()
{
    QColor input = QColorDialog::getColor (Qt::white, this);
    if (input.isValid ())
    {
        int r, g, b, a;
        input.getRgb (&r, &g, &b, &a);

        const Color color = Color (r, g, b, a);
        const int count = colorListModel.rowCount ();

        colorListModel.insertRow (count);
        colorListModel.setData (colorListModel.index (count), QVariant::fromValue (color));
    }
}

/**
 * Handles converting the color palette of the loaded image (by calling the
 *  color_converter CLI) and displaying the converted image to the user.
 */
void Aerodlyn::ColorConvertWindow::handleConvertColor () {}

/**
 * Handles deleting the selected Color instances from the user's stored palette.
 */
void Aerodlyn::ColorConvertWindow::handleDeleteColor ()
{
    QModelIndexList indexes = ui->colorListView->selectionModel ()->selectedIndexes ();
    std::sort (indexes.begin (), indexes.end ());

    for (QModelIndexList::reverse_iterator it = indexes.rbegin (); it != indexes.rend (); it++)
        colorListModel.removeRow (it->row ());
}
