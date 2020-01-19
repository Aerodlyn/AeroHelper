#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <cstdio>
#include <iostream>

#include <QApplication>
#include <QTextStream>

class Utils
{
    public: // Methods
        static bool isInCircle (const double x, const double y, const double cx, const double cy, const double cr);

        static QString getTitle ();
        static QString getVersion ();
};

#endif // UTILS_H
