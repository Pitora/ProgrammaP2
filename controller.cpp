#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{

}

void Controller::setWindow(Window* w){ window = w;
                                     getBoxItems();}

void Controller::setCollection(Collection* c){ col = c;}

void Controller::setCodex(Codex* co){codex = co;}

void Controller::setAddItem(AddItem* a){ add = a;}

QList<QString> Controller::getItemsNames()
{
   C<DeepPtr<Obj>> a;
   a = col->getAllObj();
   QList<QString> names;
   for(auto i = a.begin(); i != a.end(); ++i){
       names.append(QString::number((*i)->getId()) + ")" + QString::fromStdString((*i)->getName()));
   }
   return names;
}

void Controller::calc() const{
    DeepPtr<Character> c = col->getChar();
    int atk = c->damage();
    int def = c->defense();

    window->calcDmgDef(atk,def);
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
    a = col->getObjType("Armor","HELM");
    for(auto i = a.begin(); i != a.end();++i){
        names.append(QString::number((*i)->getId()) + ")" + QString::fromStdString((*i)->getName()));
    }
    window->loadBox(names,2);

    names.clear();
    a = col->getObjType("Armor","CHEST");
    for(auto i = a.begin(); i != a.end();++i){
        names.append(QString::number((*i)->getId()) + ")" + QString::fromStdString((*i)->getName()));
    }
    window->loadBox(names,3);

    names.clear();
    a = col->getObjType("Armor","GLOVES");
    for(auto i = a.begin(); i != a.end();++i){
        names.append(QString::number((*i)->getId()) + ")" + QString::fromStdString((*i)->getName()));
    }
    window->loadBox(names,4);

    names.clear();
    a = col->getObjType("Armor","BOOTS");
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
    add = new AddItem(1,this);
    add->exec();
}

void Controller::createArmorDialog() {
    add = new AddItem(2,this);
    add->exec();
}

void Controller::createConsumableDialog(){
    add = new AddItem(3,this);
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

void Controller::eliminateObj(){
    QString s = codex->getSelectedItem();
    if(!s.isNull()){
    QString subString = s.mid(0,s.indexOf(')'));
    int id = subString.toInt();
    col->remove(id);
    codex->refreshCodex(getItemsNames());
    }
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

void Controller::getInfoObj(QListWidgetItem *item)
{
    QString s = item->text();
    QString subString = s.mid(0,s.indexOf(')'));
    int id = subString.toInt();
    s = QString::fromStdString(col->getInfoObj(id));
    codex->showDetails(s);
}

void Controller::showCodex()
{

    codex = new Codex(this,getItemsNames());
    codex->exec();
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
        QString path = codex->showImportDialog();
        col->importObj(path.toStdString());
        codex->refreshCodex(getItemsNames());
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
    try {
        QString path = codex->showExpDialog();
        QString s = codex->getSelectedItem();
        QString subString = s.mid(0,s.indexOf(')'));
        int id = subString.toInt();
        col->exportObj(id,path.toStdString());
        //metodo/i che refreshano la finestra
    } catch (std::runtime_error exc) {
        //view->showWarning(exc.what());
    }

}
