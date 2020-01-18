#include "VertexDataSetCollection.h"

/**
 * Represents a collection of data sets, each identified by a user-typed name.
 *
 * @author  Patrick Jahnig (Aerodlyn)
 * @version 2020.01.16
 */

/* Public Methods */
/**
 * Determines if the collection has a vertex data set with the given name.
 *
 * @param name - The name of the data set to check the existance of
 *
 * @return True if a data set with the given name exists in the collection, false
 *  otherwise
 */
bool Aerodlyn::VertexDataSetCollection::contains (const QString &name) const
{
    for (auto it = sets.begin (); it != sets.end (); it++)
    {
        if (it->name.compare (name) == 0)
            return true;
    }

    return false;
}

/**
 * Removes the vertex data set with the given name.
 *
 * @param name - The name of the data set to remove
 *
 * @return True if the data set was removed (i.e. the given name matched an existing
 *  data set), false otherwise
 */
bool Aerodlyn::VertexDataSetCollection::remove (const QString &name)
{
    for (int i = 0; i < sets.length (); i++)
    {
        if (sets.at (i).name.compare (name) == 0)
        {
            sets.remove (i);
            return true;
        }
    }

    return false;
}

/**
 * Creates and adds a new vertex data set with the given name. This method will not
 *  create duplicate data sets, so names must be unique.
 *
 * @param name - The name of the data set to create and add
 *
 * @return The index of the added data set (sorted alphabetically) if the given name
 *  is unique and the data set was successfully created and added, -1 otherwise
 */
int Aerodlyn::VertexDataSetCollection::add (const QString name)
{
    auto it = sets.begin ();
    for (; it != sets.end (); it++)
    {
        const int comparison = it->name.compare (name);

        if (comparison == 0)
            return -1;

        else if (comparison > 0)
            break;
    }

    it = sets.insert (it, { name, QPolygonF () });
    return static_cast <int> (std::distance (sets.begin (), it));
}

/**
 * Returns the current number of data sets in this collection.
 *
 * @return The current number of data sets in this collection
 */
int Aerodlyn::VertexDataSetCollection::length () const
    { return sets.length (); }

/**
 * Returns the region represented by the vertex data set with the given name, if one exists.
 *
 * @param name - The name of the data set to return
 *
 * @return The region represented by the data set with the given name if one exists. If one does
 *  not exist, then an empty optional is returned
 */
std::optional <std::reference_wrapper <QPolygonF>> Aerodlyn::VertexDataSetCollection::get (const QString &name)
{
    for (auto it = sets.begin (); it != sets.end (); it++)
    {
        if (it->name.compare (name) == 0)
            return std::optional <std::reference_wrapper <QPolygonF>> { it->region };
    }

    return std::nullopt;
}
