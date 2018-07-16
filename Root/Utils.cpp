#include "Utils.h"

bool Utils::isInCircle (const float x, const float y, const float cx, const float cy, const float cr)
{
    float dx = abs (x - cx), dy = abs (y - cy);

    if (dx > cr || dy > cr)
        return false;

    else
        return (dx + dy <= cr) || (pow (dx, 2) + pow (dy, 2) <= pow (cr, 2));
}

QString Utils::getTitle () { return QString ("AeroHelper | Ver: ").append (getVersion ()); }

QString Utils::getVersion ()
{
    FILE *file = fopen (QApplication::applicationDirPath ().append ("/VERSION").toStdString ().c_str (), "r");

    QString str = file ? QTextStream (file).readAll () : QString ("VERSION couldn't be loaded...");

    fclose (file);
    return str;
}