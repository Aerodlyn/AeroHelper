#ifndef VERTEXDATASETCOLLECTION_H
#define VERTEXDATASETCOLLECTION_H

#include <functional>
#include <iterator>
#include <optional>

#include <QPolygonF>
#include <QVector>

#include "VertexDataSet.h"

namespace Aerodlyn
{
    /**
     * Represents a collection of data sets, each identified by a user-typed name.
     *
     * @author  Patrick Jahnig (Aerodlyn)
     * @version 2020.01.14
     */
    class VertexDataSetCollection
    {
        private: // Fields
            QVector <VertexDataSet> sets;

        public: // Methods
            /**
             * Determines if the collection has a vertex data set with the given name.
             *
             * @param name - The name of the data set to check the existance of
             *
             * @return True if a data set with the given name exists in the collection, false
             *  otherwise
             */
            bool contains (const QString &name) const;

            /**
             * Removes the vertex data set with the given name.
             *
             * @param name - The name of the data set to remove
             *
             * @return True if the data set was removed (i.e. the given name matched an existing
             *  data set), false otherwise
             */
            bool remove (const QString &name);

            /**
             * Creates and adds a new vertex data set with the given name. This method will not
             *  create duplicate data sets, so names must be unique.
             *
             * @param name - The name of the data set to create and add
             *
             * @return The index of the added data set (sorted alphabetically) if the given name
             *  is unique and the data set was successfully created and added, -1 otherwise
             */
            int add (const QString name);

            /**
             * Returns the current number of data sets in this collection.
             *
             * @return The current number of data sets in this collection
             */
            int length () const;

            /**
             * Returns the region represented by the vertex data set with the given name, if one exists.
             *
             * @param name - The name of the data set to return
             *
             * @return The region represented by the data set with the given name if one exists. If one does
             *  not exist, then an empty optional is returned
             */
            std::optional <std::reference_wrapper <QPolygonF>> get (const QString &name);
    };
}

#endif
