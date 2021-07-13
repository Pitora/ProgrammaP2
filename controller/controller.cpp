#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{

}

void Controller::setWindow(Window* w){ window = w;
                                     refreshWindow();}

void Controller::setCollection(Collection* c){ col = c;}

void Controller::setCodex(Codex* co){codex = co;}

void Controller::setAddItem(AddItem* a){ add = a;}

void Controller::refreshWindow()
{
    getBoxItems();
    setWindowChar();
}

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

void Controller::calc() const {

    int atk = col->getCharAtk();
    int def = col->getCharDef();

    window->calcDmgDef(atk,def);
}

void Controller::getBoxItems()
{
    C<DeepPtr<Obj>> a;
    a = col->getObjType("Weapon","");
    QList<QString> names;
    for(auto i = a.begin(); i != a.end();++i){
        names.append(QString::number((*i)->getId()) + ')' + QString::fromStdString((*i)->getName()));
    }
    window->loadBox(names,1);

    names.clear();
    a = col->getObjType("Armor","HELM");
    for(auto i = a.begin(); i != a.end();++i){
        names.append(QString::number((*i)->getId()) + ')' + QString::fromStdString((*i)->getName()));
    }
    window->loadBox(names,2);

    names.clear();
    a = col->getObjType("Armor","CHEST");
    for(auto i = a.begin(); i != a.end();++i){
        names.append(QString::number((*i)->getId()) + ')' + QString::fromStdString((*i)->getName()));
    }
    window->loadBox(names,3);

    names.clear();
    a = col->getObjType("Armor","GLOVES");
    for(auto i = a.begin(); i != a.end();++i){
        names.append(QString::number((*i)->getId()) + ')' + QString::fromStdString((*i)->getName()));
    }
    window->loadBox(names,4);

    names.clear();
    a = col->getObjType("Armor","BOOTS");
    for(auto i = a.begin(); i != a.end();++i){
        names.append(QString::number((*i)->getId()) + ')' + QString::fromStdString((*i)->getName()));
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

void Controller::setWindowChar(){
    //per reimpostare dopo refresh
    QString name = QString::fromStdString(col->getCharName());
    //metodo che setta nome sulla view
    window->setBuildName(name);

    C<int> stats = col->getCharStats();
    QList<QString> statsQ;
    for (auto i = stats.begin(); i != stats.end(); ++i)
    {
        statsQ.append(QString::number(*i));
    }
    //metodo che setta le statistiche
    window->setStats(statsQ);

    DeepPtr<Weapon> w = col->getCharWeapon();
    //elaborazione e metodo che setta sulla window l'oggetto equipaggiato
    QString s = (QString::number(w->getId())+ ')' + QString::fromStdString(w->getName()));
    window->setWeapon(s);

    C<DeepPtr<Armor>> a = col->getCharArmor();
    QList<QString> ls;
    for (auto i = a.begin(); i != a.end(); ++i)
    {
        ls.append((QString::number((*i)->getId())+ ')' + QString::fromStdString((*i)->getName())));
    }
    //stessa cosa ma più complicato
    window->setArmor(ls);

    prevId.clear();
    C<DeepPtr<Consumable>> inv = col->getCharCons();
    QList<QString> x;
    for (auto i = inv.begin(); i != inv.end(); ++i)
    {
        x.append((QString::number((*i)->getId())+ ')' + QString::fromStdString((*i)->getName())));
        prevId.append((*i)->getId());
    }
    window->setItems(x);
    calc();
    //stessa cosa ma leggermente più complicato


}

void Controller::setVitality(QString x) {
    col->setCharVit(x.toInt());
    calc();
}
void Controller::setStrenght(QString x){
    col->setCharStr(x.toInt());
    calc();
}
void Controller::setDexterity(QString x){
    col->setCharDex(x.toInt());
    calc();
}
void Controller::setAim(QString x){
    col->setCharAim(x.toInt());
    calc();
}


void Controller::changeName(QString s){
    if(s.isEmpty()){
        s = "Build Name";
    }
    col->modifyCharName(s.toStdString());
}
void Controller::changeWeapon(QString s){
    QString subString = s.mid(0,s.indexOf(')'));
    int id = subString.toInt();
    col->modifyCharWeap(id);
    calc();
}
void Controller::changeArmor(QString s){
    QString subString = s.mid(0,s.indexOf(')'));
    int id = subString.toInt();
    col->modifyCharArmorAlt(id);
    calc();
}

void Controller::changeItem1(QString s)
{
    QString subString = s.mid(0,s.indexOf(')'));
    int id = subString.toInt();
    col->modifyCharInv(id,prevId[0]);
    prevId[0] = id;
}

void Controller::changeItem2(QString s)
{
    QString subString = s.mid(0,s.indexOf(')'));
    int id = subString.toInt();
    col->modifyCharInv(id,prevId[1]);
    prevId[1] = id;
}

void Controller::changeItem3(QString s)
{
    QString subString = s.mid(0,s.indexOf(')'));
    int id = subString.toInt();
    col->modifyCharInv(id,prevId[2]);
    prevId[2] = id;
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
        QString path = window->importCharDialog();
        col->importChara(path.toStdString());
        refreshWindow();
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
    } catch (std::runtime_error exc) {
        //view->showWarning(exc.what());
    }

}

void Controller::exportChar()  //per esportare
{
    try {
        QString path = window->exportCharDialog();
        col->exportChara(path.toStdString());
        //metodo/i che refreshano la finestra
    } catch (std::runtime_error exc) {
        //view->showWarning(exc.what());
    }

}

void Controller::exportObj()  //per edportare
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
