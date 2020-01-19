#ifndef VERTEXDATASET_H
#define VERTEXDATASET_H

#include <QString>
#include <QPolygonF>

namespace Aerodlyn
{
    /**
     * A pair that is the representation of a series of points making up a polygonal region of
     *  vertices, with a name.
     *
     * @author  Patrick Jahnig (Aerodlyn)
     * @version 2019.01.14
     */
    struct VertexDataSet
    {
        QString   name;
        QPolygonF region;
    };
}

#endif
