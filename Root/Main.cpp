#include <QApplication>

#include "VertexEditor/VertexEditorWindow.h"

int main (int argc, char *argv [])
{
    QApplication a (argc, argv);

    Aerodlyn::VertexEditorWindow vertexWindow;
    vertexWindow.show ();

    return a.exec ();
}
