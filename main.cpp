#include "view/window.h"
#include "controller/controller.h"
#include "model/collection.h"
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
