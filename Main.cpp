#include <QApplication>

#include "VertexEditorWindow.h"

int main (int argc, char *argv [])
{
    QApplication a (argc, argv);

    VertexEditorWindow vertexWindow;
    vertexWindow.show ();

    return a.exec ();
}
