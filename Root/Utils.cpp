#include "Utils.h"

/* Public Methods */
/**
 * Determines if the given point is within a circle defined by a given center point
 *  and radius.
 *
 * @param x  - The x-coordinate of the point to test
 * @param y  - The y-coordinate of the point to test
 * @param cx - The x-coordinate of the circle, in which it's center lies
 * @param cy - The y-corrdinate of the circle, in which it's center lies
 * @param cr - The radius of the circle
 *
 * @return True if the given point is within the given circle definition, false otherwise
 */
bool Aerodlyn::Utils::isInCircle (const double x, const double y, const double cx, const double cy, const double cr)
{
    const double dx = abs (x - cx), dy = abs (y - cy);

    if (dx > cr || dy > cr)
        return false;

    else
        return (dx + dy <= cr) || pow (dx, 2) + pow (dy, 2) <= pow (cr, 2);
}

/**
 * Determines if the given point is within a circle defined by a given center point
 *  and radius.
 *
 * @param point  - The point to test
 * @param center - The center point of the circle
 * @param radius - The radius of the circle
 *
 * @return True if the given point is within the given circle definition, false otherwise
 */
bool Aerodlyn::Utils::isInCircle (const QPointF point, const QPointF center, const double radius)
    { return isInCircle (point.x (), point.y (), center.x (), center.y (), radius); }

QString Aerodlyn::Utils::getTitle () { return QString ("AeroHelper | Ver: ").append (getVersion ()); }

QString Aerodlyn::Utils::getVersion ()
{
    FILE *file = fopen (QApplication::applicationDirPath ().append ("/VERSION").toStdString ().c_str (), "r");

    QString str = file ? QTextStream (file).readAll () : QString ("VERSION couldn't be loaded...");

    fclose (file);
    return str;
}
