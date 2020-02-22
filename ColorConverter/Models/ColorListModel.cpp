#include "ColorListModel.h"

/**
 * This class handles the storage of the colors that make up the palette.
 *
 * @author  Patrick Jahnig (Aerodlyn)
 * @version 2020.02.19
 */

/* Constructors/Deconstructors */
Aerodlyn::ColorListModel::ColorListModel () : QAbstractListModel () {}

/* Public overridden methods */
bool Aerodlyn::ColorListModel::insertRows (int position, int rows, const QModelIndex &parent)
{
    Q_UNUSED (parent);

    beginInsertRows (QModelIndex (), position, position + rows - 1);

    for (int i = 0; i < rows; i++)
        colors.insert (position, QVariant::fromValue (Color ()));

    endInsertRows ();
    return true;
}

bool Aerodlyn::ColorListModel::removeRows (int position, int rows, const QModelIndex &parent)
{
    Q_UNUSED (parent);

    beginRemoveRows (QModelIndex (), position, position + rows - 1);

    for (int i = 0; i < rows; i++)
        colors.remove (position);

    endRemoveRows ();
    return true;
}

bool Aerodlyn::ColorListModel::setData (const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid () && role == Qt::EditRole)
    {
        colors.replace (index.row (), value);
        emit dataChanged (index, index, { role });

        return true;
    }

    return false;
}

int Aerodlyn::ColorListModel::rowCount (const QModelIndex &parent) const
{
    Q_UNUSED (parent);
    return colors.size ();
}

Qt::ItemFlags Aerodlyn::ColorListModel::flags (const QModelIndex &index) const
{
    if (!index.isValid ())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags (index) | Qt::ItemIsEditable;
}

QVariant Aerodlyn::ColorListModel::data (const QModelIndex &index, int role) const
{
    if (!index.isValid () || index.row () >= rowCount ())
        return QVariant ();

    Color color = colors.at (index.row ()).value <Color> ();
    switch (role)
    {
        case Qt::DecorationRole:
            return QColor (color.r (), color.g (), color.b (), color.a ());

        case Qt::DisplayRole:
            return QStringLiteral ("%1").arg (color.hex ());

        case Qt::ToolTipRole:
            return QStringLiteral ("R: %1, G: %2, B: %3, A: %4")
                .arg (color.r ())
                .arg (color.g ())
                .arg (color.b ())
                .arg (color.a ());

        default:
            return QVariant ();
    }
}

/* Public methods */
/**
 * Returns the space-delimited hexadecimal string of all the colors that make up the
 *  stored palette.
 *
 * @return The space-delimited hexadecimal string of all stored colors
 */
QString Aerodlyn::ColorListModel::dataToHex () const
{
    if (rowCount () == 0)
        return QStringLiteral ();

    QString hexCodes = QStringLiteral ("%1").arg (colors.first ().value <Color> ().hex ());
    for (QVector <QVariant>::const_iterator it = colors.begin () + 1; it != colors.end (); it++)
        hexCodes = QStringLiteral ("%1 %2").arg (hexCodes).arg (it->value <Color> ().hex ());

    return hexCodes;
}
