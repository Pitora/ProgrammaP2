#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{

}

void Controller::setWindow(Window* w){ window = w;
                                     getBoxItems();}

void Controller::setCollection(Collection* c){ col = c;}

void Controller::calc() const{
    window->calcDmgDef();
}

void Controller::getBoxItems()
{
    C<DeepPtr<Obj>> a;
    a = col->getObjType("Weapon","");
    QList<QString> names;
    for(auto i = a.begin(); i != a.end();++i){
        names.append(QString::number((*i)->getId()) + ")" + QString::fromStdString((*i)->getName()));
    }
    window->loadBox(names,1);

    names.clear();
    a = col->getObjType("Armor","Elmo");
    for(auto i = a.begin(); i != a.end();++i){
        names.append(QString::number((*i)->getId()) + ")" + QString::fromStdString((*i)->getName()));
    }
    window->loadBox(names,2);

    names.clear();
    a = col->getObjType("Armor","Petto");
    for(auto i = a.begin(); i != a.end();++i){
        names.append(QString::number((*i)->getId()) + ")" + QString::fromStdString((*i)->getName()));
    }
    window->loadBox(names,3);

    names.clear();
    a = col->getObjType("Armor","Guanti");
    for(auto i = a.begin(); i != a.end();++i){
        names.append(QString::number((*i)->getId()) + ")" + QString::fromStdString((*i)->getName()));
    }
    window->loadBox(names,4);

    names.clear();
    a = col->getObjType("Armor","Stivali");
    for(auto i = a.begin(); i != a.end();++i){
        names.append(QString::number((*i)->getId()) + ")" + QString::fromStdString((*i)->getName()));
    }
    window->loadBox(names,5);

    names.clear();
    a = col->getObjType("Consumable","");
    for(auto i = a.begin(); i != a.end();++i){
        names.append(QString::number((*i)->getId()) + ")" + QString::fromStdString((*i)->getName()));
    }
    window->loadBox(names,6);

}

void Controller::createWeapon() {
    addItem* add = new addItem(1,this);
    add->exec();
}

void Controller::createArmor() {
    addItem* add = new addItem(2,this);
    add->exec();
}

void Controller::createConsumable(){
    addItem* add = new addItem(3,this);
    add->exec();
}

void Controller::showCodex()
{
    Codex* cod = new Codex();
    cod->show();
}


void Controller::importChar()  //per importare
{
    /*	try {
        QString path = view->showAddDialog();
        model->addNewSlide(path.toStdString());
    } catch (std::runtime_error exc) {
        view->showWarning(exc.what());
    }*/

}
