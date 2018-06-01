#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <cstdio>

#include <QApplication>
#include <QTextStream>

class Utils
{
    public:
        static bool isInCircle (const float x, const float y, const float cx, const float cy, const float cr);

        static QString getTitle ();
        static QString getVersion ();
};

#endif
