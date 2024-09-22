#include <QApplication>
#include "wikieditor.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    WikiEditor editor;
    editor.show();

    return app.exec();
}
