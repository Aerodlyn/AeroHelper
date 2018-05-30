#include "Utils.h"

QString Utils::getTitle () { return QString ("AeroHelper | Ver: ").append (getVersion ()); }

QString Utils::getVersion ()
{
    FILE *file = fopen (QApplication::applicationDirPath ().append ("/VERSION").toStdString ().c_str (), "r");

    QString str = file ? QTextStream (file).readAll () : QString ("VERSION couldn't be loaded...");

    fclose (file);
    return str;
}
