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
    std::cout<<"collection settata"<<std::endl;
    c.setWindow(&w);
    std::cout<<"window settata"<<std::endl;
    w.setController(&c);
    std::cout<<"controller settata"<<std::endl;
    w.show();

    return a.exec();
}
