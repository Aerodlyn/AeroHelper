#ifndef COLOR_CONVERT_WINDOW_H
#define COLOR_CONVERT_WINDOW_H

#include <algorithm>

#include <QColor>
#include <QColorDialog>
#include <QList>
#include <QObject>
#include <QMainWindow>
#include <QModelIndexList>

#include "ColorConverter/Delegates/ColorListDelegate.h"
#include "ColorConverter/Models/ColorListModel.h"
#include "ColorConverter/Utilities/Color.h"

namespace Ui
    { class ColorConvertWindow; }

namespace Aerodlyn
{
    /**
     * This class handles creating a GUI to facilitate visual interaction with the color_converter
     *  CLI tool.
     *
     * @author  Patrick Jahnig (Aerodlyn)
     * @version 2020.02.19
     */
    class ColorConvertWindow : public QMainWindow
    {
        Q_OBJECT

        private: // Fields
            ColorListDelegate      colorListDelegate;
            ColorListModel         colorListModel;

            Ui::ColorConvertWindow *ui;

        public: // Constructors/Deconstructors
            /**
             * Creates a new ColorConvertWindow instance with the optional parent.
             *
             * @param parent - The QWidget to treat as the parent of this ColorConvertWindow
             *  instance
             */
            explicit ColorConvertWindow (QWidget *parent = nullptr);

            ~ColorConvertWindow ();

        private slots:
            /**
             * Handles adding a new Color instance to the user's stored palette.
             */
            void handleAddColor ();

            /**
             * Handles converting the color palette of the loaded image (by calling the
             *  color_converter CLI) and displaying the converted image to the user.
             */
            void handleConvertColor ();

            /**
             * Handles deleting the selected Color instances from the user's stored palette.
             */
            void handleDeleteColor ();
    };
}

#endif // COLOR_CONVERT_WINDOW_H
