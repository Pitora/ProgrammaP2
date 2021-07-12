#include "window.h"
#include "controller.h"
#include "Classes/collection.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Collection col;
    Controller c;
    Window w;

    c.setCollection(&col);
    c.setWindow(&w);
    w.setController(&c);
    w.show();

    return a.exec();
}
