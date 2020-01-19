#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <cstdio>
#include <iostream>

#include <QApplication>
#include <QPointF>
#include <QTextStream>

namespace Aerodlyn
{
    class Utils
    {
        public: // Methods
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
            static bool isInCircle (const double x, const double y, const double cx, const double cy, const double cr);

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
            static bool isInCircle (const QPointF point, const QPointF center, const double radius);

            static QString getTitle ();
            static QString getVersion ();
    };
}

#endif // UTILS_H
