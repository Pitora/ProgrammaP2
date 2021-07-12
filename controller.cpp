#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{

}

void Controller::setWindow(Window* w){ window = w;
                                     getBoxItems();}

void Controller::setCollection(Collection* c){ col = c;}

void Controller::calc() const{
    DeepPtr<Character> c = col->getChar();
    int atk = c->damage();
    int def = c->defense();


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

void Controller::createWeaponDialog() {
    addItem* add = new addItem(1,this);
    add->exec();
}

void Controller::createArmorDialog() {
    addItem* add = new addItem(2,this);
    add->exec();
}

void Controller::createConsumableDialog(){
    addItem* add = new addItem(3,this);
    add->exec();
}

void Controller::createMelee(QString n, int w, int c, int r, int rav, int cc, int s_str, int s_dex, int s_aim, QString a_t, QString a_e, int d){
    col->add(n.toStdString(),w,c,r,rav,cc,s_str,s_dex,s_aim,a_t.toStdString(),a_e.toStdString(),d);
    //metodo che ricarica la view principale
}
void Controller::createRanged(QString n, int w, int c, int r, int rav, int cc, int s_str, int s_dex, int s_aim, int rec, int rel, int m){
    col->add(n.toStdString(),w,c,r,rav,cc,s_str,s_dex,s_aim,rec,rel,m);
    //metodo che ricarica la view principale e le combobox
}
void Controller::createArmor(QString n, QString a_t, QString r, int d_v, int d){
    col->add(n.toStdString(), a_t.toStdString(), r.toStdString(), d_v, d);
}
void Controller::createHealing(QString n, QString a_v, int p){
    col->add(n.toStdString(),a_v.toStdString(),p);
}
void Controller::createBuff(QString n, QString e, int p, int d){
    col->add(n.toStdString(),e.toStdString(),p,d);
}

void Controller::eliminateObj(int id){
    col->remove(id);
}

void Controller::setChar(){
    DeepPtr<Character> c = col->getChar();
    //cose
}
void Controller::setVitality(int x) {
    col->setCharVit(x);
    calc();
}
void Controller::setStrenght(int x){
    col->setCharStr(x);
    calc();
}
void Controller::setDexterity(int x){
    col->setCharDex(x);
    calc();
}
void Controller::setAim(int x){
    col->setCharAim(x);
    calc();
}
void Controller::changeName(QString s){
    col->modifyCharName(s.toStdString());
}
void Controller::changeWeapon(int id){
    col->modifyCharWeap(id);
    calc();
}
void Controller::changeArmor(int id1, int id2){
    col->modifyCharArmor(id1,id2);
}
void Controller::changeItem(int id1, int id2){
    col->modifyCharInv(id1,id2);
}

void Controller::showCodex()
{
    Codex* cod = new Codex();
    cod->show();
}



void Controller::importChar()  //per importare
{
    try {
        QString path = window->importFileDialog();
        col->importChara(path.toStdString());
        //metodo/i che refreshano la finestra
    } catch (std::runtime_error exc) {
        //window->showWarning(exc.what());

    }
}

void Controller::importObj()  //per importare
{
    try {
        QString path = window->importFileDialog();
        col->importObj(path.toStdString());
        //metodo/i che refreshano la finestra
    } catch (std::runtime_error exc) {
        //view->showWarning(exc.what());
    }

}

void Controller::exportChar()  //per importare
{
//    try {
//        QString path = window->importFileDialog();
//        col->importChara(path.toStdString());
//        //metodo/i che refreshano la finestra
//    } catch (std::runtime_error exc) {
//        view->showWarning(exc.what());
//    }

}

void Controller::exportObj()  //per importare
{
//    try {
//        QString path = window->importFileDialog();
//        col->importChara(path.toStdString());
//        //metodo/i che refreshano la finestra
//    } catch (std::runtime_error exc) {
//        view->showWarning(exc.what());
//    }

}
