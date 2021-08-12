#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{

}

//setta le variabili di controller
void Controller::setWindow(Window* w){ window = w;
                                     refreshWindow();}
void Controller::setCollection(Collection* c){ col = c;}
void Controller::setCodex(Codex* co){codex = co;}
void Controller::setAddItem(AddItem* a){ add = a;}

//refresha la main window
void Controller::refreshWindow()
{
    getBoxItems();
    setWindowChar();
}

//restituisce una lista con i nomi degli oggetti
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

//calcola i valori di attacco e def
void Controller::calc() {

    int atk = col->getCharAtk(0);
    int def = col->getCharDef(0);

    window->calcDmgDef(atk,def);
}

//ottiene i dati per popolare le combobox
void Controller::getBoxItems()
{
    C<DeepPtr<Obj>> a;
    a = col->getObjPerType("Weapon","all");
    QList<QString> names;
    for(auto i = a.begin(); i != a.end();++i){
        names.append(QString::number((*i)->getId()) + ')' + QString::fromStdString((*i)->getName()));
    }
    window->loadBox(names,1);

    names.clear();
    a = col->getObjPerType("Armor","HELM");
    for(auto i = a.begin(); i != a.end();++i){
        names.append(QString::number((*i)->getId()) + ')' + QString::fromStdString((*i)->getName()));
    }
    window->loadBox(names,2);

    names.clear();
    a = col->getObjPerType("Armor","CHEST");
    for(auto i = a.begin(); i != a.end();++i){
        names.append(QString::number((*i)->getId()) + ')' + QString::fromStdString((*i)->getName()));
    }
    window->loadBox(names,3);

    names.clear();
    a = col->getObjPerType("Armor","GLOVES");
    for(auto i = a.begin(); i != a.end();++i){
        names.append(QString::number((*i)->getId()) + ')' + QString::fromStdString((*i)->getName()));
    }
    window->loadBox(names,4);

    names.clear();
    a = col->getObjPerType("Armor","BOOTS");
    for(auto i = a.begin(); i != a.end();++i){
        names.append(QString::number((*i)->getId()) + ')' + QString::fromStdString((*i)->getName()));
    }
    window->loadBox(names,5);

    names.clear();
    a = col->getObjPerType("Consumable","all");
    for(auto i = a.begin(); i != a.end();++i){
        names.append(QString::number((*i)->getId()) + ")" + QString::fromStdString((*i)->getName()));
    }
    window->loadBox(names,6);

}

//mostra la finestra di creazione di Weapon
void Controller::createWeaponDialog() {
    add = new AddItem(1,this);
    add->exec();
}

//mostra la finestra di creazione di Armor
void Controller::createArmorDialog() {
    add = new AddItem(2,this);
    add->exec();
}

//mostra la finestra di creazione di Consumable
void Controller::createConsumableDialog(){
    add = new AddItem(3,this);
    add->exec();
}

//passa i dati per creare una Melee Weapon
void Controller::createMelee(QString n, int w, int c, int r, int rav, int cc, int s_str, int s_dex, int s_aim, QString a_t, QString a_e, int d){
    col->add(n.toStdString(),w,c,r,rav,cc,s_str,s_dex,s_aim,a_t.toStdString(),a_e.toStdString(),d);
}

//passa i dati per creare una Ranged Weapon
void Controller::createRanged(QString n, int w, int c, int r, int rav, int cc, int s_str, int s_dex, int s_aim, int rec, int rel, int m){
    col->add(n.toStdString(),w,c,r,rav,cc,s_str,s_dex,s_aim,rec,rel,m);
}

//passa i dati per creare un Armor
void Controller::createArmor(QString n, QString a_t, QString r, int d_v, int d){
    col->add(n.toStdString(), a_t.toStdString(), r.toStdString(), d_v, d);
}

//passa i dati per creare un Healing Consumable
void Controller::createHealing(QString n, QString a_v, int p){
    col->add(n.toStdString(),a_v.toStdString(),p);
}

//passa i dati per creare un Buff Consumable
void Controller::createBuff(QString n, QString e, int p, int d){
    col->add(n.toStdString(),e.toStdString(),p,d);
}

//passa i dati per eliminare un oggetto
void Controller::eliminateObj(){
    QString s = codex->getSelectedItem();
    if(!s.isNull()){
        QString subString = s.mid(0,s.indexOf(')'));
        int id = subString.toInt();
        col->remove(id);
        codex->refreshCodex(getItemsNames());
    }
}

//imposta la view quando si carica una build(anche quella di default)
void Controller::setWindowChar(){
    QString name = QString::fromStdString(col->getCharName(0));
    window->setBuildName(name);

    C<int> stats = col->getCharStats(0);
    QList<QString> statsQ;
    for (auto i = stats.begin(); i != stats.end(); ++i)
    {
        statsQ.append(QString::number(*i));
    }
    window->setStats(statsQ);

    DeepPtr<Weapon> w = col->getCharWeapon(0);
    QString s = (QString::number(w->getId())+ ')' + QString::fromStdString(w->getName()));
    window->setWeapon(s);

    C<DeepPtr<Armor>> a = col->getCharArmor(0);
    QList<QString> ls;
    for (auto i = a.begin(); i != a.end(); ++i)
    {
        ls.append((QString::number((*i)->getId())+ ')' + QString::fromStdString((*i)->getName())));
    }
    window->setArmor(ls);

    prevId.clear();
    C<DeepPtr<Consumable>> inv = col->getCharCons(0);
    QList<QString> x;
    for (auto i = inv.begin(); i != inv.end(); ++i)
    {
        x.append((QString::number((*i)->getId())+ ')' + QString::fromStdString((*i)->getName())));
        prevId.append((*i)->getId());
    }
    window->setItems(x);
    calc();


}

void Controller::setVitality(QString x) {
    col->setCharVit(0,x.toInt());
    calc();
}
void Controller::setStrenght(QString x){
    col->setCharStr(0,x.toInt());
    calc();
}
void Controller::setDexterity(QString x){
    col->setCharDex(0,x.toInt());
    calc();
}
void Controller::setAim(QString x){
    col->setCharAim(0,x.toInt());
    calc();
}

//Metodi per cambiare l'equipaggiamento del Character e il nome della build
void Controller::changeName(QString s){
    if(s.isEmpty()){
        s = "Build Name";
    }
    col->modifyCharName(0,s.toStdString());
}
void Controller::changeWeapon(QString s){
    QString subString = s.mid(0,s.indexOf(')'));
    int id = subString.toInt();
    col->modifyCharWeap(0,id);
    calc();
}
void Controller::changeArmor(QString s){
    QString subString = s.mid(0,s.indexOf(')'));
    int id = subString.toInt();
    col->modifyCharArmorAlt(0,id);
    calc();
}
void Controller::changeItem1(QString s)
{
    QString subString = s.mid(0,s.indexOf(')'));
    int id = subString.toInt();
    col->modifyCharInv(0,id,prevId[0]);
    prevId[0] = id;
}
void Controller::changeItem2(QString s)
{
    QString subString = s.mid(0,s.indexOf(')'));
    int id = subString.toInt();
    col->modifyCharInv(0,id,prevId[1]);
    prevId[1] = id;
}
void Controller::changeItem3(QString s)
{
    QString subString = s.mid(0,s.indexOf(')'));
    int id = subString.toInt();
    col->modifyCharInv(0,id,prevId[2]);
    prevId[2] = id;
}

//restituisce i dettagli di un oggettp
void Controller::getInfoObj(QListWidgetItem *item)
{
    QString s = item->text();
    QString subString = s.mid(0,s.indexOf(')'));
    int id = subString.toInt();
    s = QString::fromStdString(col->getInfoObj(id));
    codex->showDetails(s);
}

//mostra la schermata codex
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
    } catch (std::runtime_error exc) {
        std::cout<<"Errore prima dell'importazione"<<std::endl;

    }
}

void Controller::importObj()  //per importare
{
    try {
        QString path = codex->showImportDialog();
        col->importObj(path.toStdString());
        codex->refreshCodex(getItemsNames());
    } catch (std::runtime_error exc) {
        std::cout<<"Errore prima dell'importazione"<<std::endl;
    }

}

void Controller::exportChar()  //per esportare
{
    try {
        QString path = window->exportCharDialog();
        col->exportChara(0, path.toStdString());
    } catch (std::runtime_error exc) {
        std::cout<<"Errore prima dell'esportazione"<<std::endl;
    }

}

void Controller::exportObj()  //per esportare
{
    try {
        QString path = codex->showExpDialog();
        QString s = codex->getSelectedItem();
        QString subString = s.mid(0,s.indexOf(')'));
        int id = subString.toInt();
        col->exportObj(id,path.toStdString());
    } catch (std::runtime_error exc) {
        std::cout<<"Errore prima dell'esportazione"<<std::endl;
    }

}
