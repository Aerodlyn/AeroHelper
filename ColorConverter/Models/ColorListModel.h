#ifndef COLOR_LIST_MODEL_H
#define COLOR_LIST_MODEL_H

#include <QAbstractListModel>
#include <QColor>
#include <QModelIndex>
#include <QString>
#include <QStringLiteral>
#include <QVariant>
#include <QVector>

#include "ColorConverter/Utilities/Color.h"

namespace Aerodlyn
{
    /**
     * This class handles the storage of the colors that make up the palette.
     *
     * @author  Patrick Jahnig (Aerodlyn)
     * @version 2020.02.19
     */
    class ColorListModel : public QAbstractListModel
    {
        private: // Fields
            QVector <QVariant> colors;

        public: // Constructors/Deconstructors
            ColorListModel ();

        public: // Overridden methods
            bool insertRows (int position, int rows, const QModelIndex &parent = QModelIndex ()) override;

            bool removeRows (int position, int rows, const QModelIndex &parent = QModelIndex ()) override;

            bool setData (const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

            int rowCount (const QModelIndex &parent = QModelIndex ()) const override;

            Qt::ItemFlags flags (const QModelIndex &index) const override;

            QVariant data (const QModelIndex &index, int role) const override;

        public: // Methods
            /**
             * Returns the space-delimited hexadecimal string of all the colors that make up the
             *  stored palette.
             *
             * @return The space-delimited hexadecimal string of all stored colors
             */
            QString dataToHex () const;
    };
}

#endif // COLOR_LIST_MODEL_H
