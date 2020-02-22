#include <QApplication>

#include "ColorConverter/ColorConvertWindow.h"
// #include "VertexEditor/VertexEditorWindow.h"

int main (int argc, char *argv [])
{
    QApplication a (argc, argv);

    // Aerodlyn::VertexEditorWindow vertexWindow;
    // vertexWindow.show ();

    Aerodlyn::ColorConvertWindow window;
    window.show ();

    return a.exec ();
}
