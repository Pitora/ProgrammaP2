#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{

}

//setta le variabili di controller
void Controller::setWindow(Window* w){ window = w;}
void Controller::setCollection(Collection* c){ col = c;}
void Controller::setCodex(Codex* co){codex = co;}
void Controller::setAddItem(AddItem* a){ add = a;}

//refresha la main window
void Controller::refreshTab()
{
    if(activeTab >= 0 && !tabs.isEmpty()){
    getBoxItems();
    std::cout<<"fatto il get box"<<std::endl;
    setWindowChar();
    std::cout<<"settato il char"<<std::endl;
    }
}

void Controller::refreshWindow()
{
    window->refresh();
}

//restituisce una lista con i nomi degli oggetti
QList<QString> Controller::getItemsNames()
{
   C<DeepPtr<Obj>> a;
   a = col->getAllObj();
   QList<QString> names;
   for(auto i = a.begin(); i != a.end(); ++i){
       names.append(QString::fromStdString((*i)->getName()));
   }
   return names;
}

QList<int> Controller::getItemsId()
{
   C<DeepPtr<Obj>> a;
   a = col->getAllObj();
   QList<int> id;
   for(auto i = a.begin(); i != a.end(); ++i){
       id.append((*i)->getId());
   }
   return id;
}

QList<QString> Controller::getCharNames()
{
    C<std::string> names;
    names = col->getCharsName();
    QList<QString> a;
    for(auto i = names.begin(); i != names.end(); ++i){
        a.append(QString::fromStdString(*i));
    }
    return a;
}

//calcola i valori di attacco e def
void Controller::calc() {

    int atk = col->getCharAtk(tabs[activeTab]->getId());
    int def = col->getCharDef(tabs[activeTab]->getId());

    tabs[activeTab]->calcDmgDef(atk,def);
}

//ottiene i dati per popolare le combobox
void Controller::getBoxItems()
{
    C<DeepPtr<Obj>> a;
    a = col->getObjPerType("Weapon","all");
    QList<QString> names;
    QList<int> id;
    for(auto i = a.begin(); i != a.end();++i){
        names.append( QString::fromStdString((*i)->getName()));
        id.append((*i)->getId());
    }
    tabs[activeTab]->loadBox(names,id,1);

    names.clear();
    id.clear();
    a = col->getObjPerType("Armor","HELM");
    for(auto i = a.begin(); i != a.end();++i){
        names.append( QString::fromStdString((*i)->getName()));
        id.append((*i)->getId());
    }
    tabs[activeTab]->loadBox(names,id,2);

    names.clear();
    id.clear();
    a = col->getObjPerType("Armor","CHEST");
    for(auto i = a.begin(); i != a.end();++i){
        names.append( QString::fromStdString((*i)->getName()));
        id.append((*i)->getId());
    }
    tabs[activeTab]->loadBox(names,id,3);

    names.clear();
    id.clear();
    a = col->getObjPerType("Armor","GLOVES");
    for(auto i = a.begin(); i != a.end();++i){
        names.append( QString::fromStdString((*i)->getName()));
        id.append((*i)->getId());
    }
    tabs[activeTab]->loadBox(names,id,4);

    names.clear();
    id.clear();
    a = col->getObjPerType("Armor","BOOTS");
    for(auto i = a.begin(); i != a.end();++i){
        names.append( QString::fromStdString((*i)->getName()));
        id.append((*i)->getId());
    }
    tabs[activeTab]->loadBox(names,id,5);

    names.clear();
    id.clear();
    a = col->getObjPerType("Consumable","all");
    for(auto i = a.begin(); i != a.end();++i){
        names.append( QString::fromStdString((*i)->getName()));
        id.append((*i)->getId());
    }
    tabs[activeTab]->loadBox(names,id,6);
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
    QVariant id = codex->getSelectedItem()->data(Qt::UserRole);
    if(!id.isNull()){
        col->remove(id.toInt());
        codex->refreshCodex(getItemsNames(),getItemsId());
    }
}

//imposta la view quando si carica una build(anche quella di default)
void Controller::setWindowChar(){

    int idChar = tabs[activeTab]->getId();
    std::cout<<"char id: "+ std::to_string(idChar)<<std::endl;
    QString name = QString::fromStdString(col->getCharName(idChar));
    tabs[activeTab]->setBuildName(name);

    std::cout<<"messo il nome"<<std::endl;

    C<int> stats = col->getCharStats(idChar);
    QList<QString> statsQ;
    for (auto i = stats.begin(); i != stats.end(); ++i)
    {
        statsQ.append(QString::number(*i));
    }
    tabs[activeTab]->setStats(statsQ);

    std::cout<<"stat"<<std::endl;

    DeepPtr<Weapon> w = col->getCharWeapon(idChar);
    int id = w->getId();
    tabs[activeTab]->setWeapon(id);

    std::cout<<"arma"<<std::endl;

    C<DeepPtr<Armor>> a = col->getCharArmor(idChar);
    QList<int> ls;
    for (auto i = a.begin(); i != a.end(); ++i)
    {
        ls.append((*i)->getId());
    }
    tabs[activeTab]->setArmor(ls);

    std::cout<<"armor"<<std::endl;

    prevId.clear();
    C<DeepPtr<Consumable>> inv = col->getCharCons(idChar);
    QList<int> x;
    for (auto i = inv.begin(); i != inv.end(); ++i)
    {
        x.append((*i)->getId());
        prevId.append((*i)->getId());
    }
    tabs[activeTab]->setItems(x);

    std::cout<<"oggetti"<<std::endl;

    calc();


}

void Controller::setVitality(QString x) {
    col->setCharVit(tabs[activeTab]->getId(),x.toInt());
    calc();
}
void Controller::setStrenght(QString x){
    col->setCharStr(tabs[activeTab]->getId(),x.toInt());
    calc();
}
void Controller::setDexterity(QString x){
    col->setCharDex(tabs[activeTab]->getId(),x.toInt());
    calc();
}
void Controller::setAim(QString x){
    col->setCharAim(tabs[activeTab]->getId(),x.toInt());
    calc();
}

//Metodi per cambiare l'equipaggiamento del Character e il nome della build
void Controller::changeName(QString s){
    if(s.isEmpty()){
        s = "Build Name";
    }
    col->modifyCharName(tabs[activeTab]->getId(),s.toStdString());
}
void Controller::changeWeapon(QVariant id){
    col->modifyCharWeap(tabs[activeTab]->getId(),id.toInt());
    calc();
}
void Controller::changeArmor(QVariant id){
    col->modifyCharArmorAlt(tabs[activeTab]->getId(),id.toInt());
    calc();
}
void Controller::changeItem1(QVariant id)
{
    col->modifyCharInv(tabs[activeTab]->getId(),id.toInt(),prevId[0]);
    prevId[0] = id.toInt();
}
void Controller::changeItem2(QVariant id)
{
    col->modifyCharInv(tabs[activeTab]->getId(),id.toInt(),prevId[1]);
    prevId[1] = id.toInt();
}
void Controller::changeItem3(QVariant id)
{
    col->modifyCharInv(tabs[activeTab]->getId(),id.toInt(),prevId[2]);
    prevId[2] = id.toInt();
}

void Controller::addTab(windowtabwidget *t)
{
    tabs.append(t);
}

void Controller::deleteTab(int index)
{
    if((index-1) == activeTab){
        //cose
    }
    tabs.removeAt(index-1);
}

void Controller::changeTab(int i)
{
    activeTab = i-1;
    if(activeTab >= 0){
        refreshTab();
    }else{
        refreshWindow();
    }
}

bool Controller::isTabOpen(int index)
{
    for (auto i = tabs.begin(); i != tabs.end(); ++i)
    {
        if ((*i)->getId() == index)
        {
            return true;
        }
    }
    return false;
}

//restituisce i dettagli di un oggetto
void Controller::getInfoObj(QListWidgetItem *item)
{
    int id = item->data(Qt::UserRole).toInt();
    QString s = QString::fromStdString(col->getInfoObj(id));
    codex->showDetails(s);
}

//mostra la schermata codex
void Controller::showCodex()
{
    codex = new Codex(this,getItemsNames(),getItemsId());
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
        codex->refreshCodex(getItemsNames(),getItemsId());
    } catch (std::runtime_error exc) {
        std::cout<<"Errore prima dell'importazione"<<std::endl;
    }

}

void Controller::exportChar()  //per esportare
{
    try {
        QString path = window->exportCharDialog();
        col->exportChara(window->getIndSelChar(), path.toStdString());
    } catch (std::runtime_error exc) {
        std::cout<<"Errore prima dell'esportazione"<<std::endl;
    }

}

void Controller::exportObj()  //per esportare
{
    try {
        QString path = codex->showExpDialog();
        int id = codex->getSelectedItem()->data(Qt::UserRole).toInt();
        col->exportObj(id,path.toStdString());
    } catch (std::runtime_error exc) {
        std::cout<<"Errore prima dell'esportazione"<<std::endl;
    }

}

void Controller::defaultChar()
{
    col->createDefaultChar();
    refreshWindow();
}

void Controller::deleteChar()
{
    int ind = window->getIndSelChar();
    bool found = false;
    int i = 0;
    while (i < tabs.count() && !found)
    {
        if (tabs[i]->getId() == ind)
        {
            found = true;
        }
        else{
            i++;
        }

    }
    if (found)
    {
        window->removeTab(i+1);
    }
    col->deleteChar(ind);
    refreshWindow();
}
