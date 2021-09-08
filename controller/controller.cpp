#include "controller.h"

//Inizio public

Controller::Controller(QObject *parent) : QObject(parent)
{

}

//setta le variabili di controller
void Controller::setWindow(Window* w){ window = w;}
void Controller::setCollection(Collection* c){ col = c;}
void Controller::setCodex(Codex* co){codex = co;}
void Controller::setAddItem(AddItem* a){ add = a;}

//refresha una tab
void Controller::refreshTab()
{
    if(activeTab >= 0 && !tabs.isEmpty()){
    getBoxItems();
    setWindowChar();
    tabs[activeTab]->resetImage();
    }
}

//refresha la main window
void Controller::refreshWindow()
{
    window->refresh();
}

//restituisce una lista con i nomi degli oggetti (filtrabile)
QList<QString> Controller::getItemsNames(std::string type , std::string type2)
{
   C<DeepPtr<Obj>> a;
   a = col->getObjPerType(type,type2);
   QList<QString> names;
   for(auto i = a.begin(); i != a.end(); ++i){
       names.append(QString::fromStdString((*i)->getName()));
   }
   return names;
}

//restituisce una lista con gli id degli oggetti (filtrabile)
QList<int> Controller::getItemsId(std::string type , std::string type2)
{
   C<DeepPtr<Obj>> a;
   a = col->getObjPerType(type,type2);
   QList<int> id;
   for(auto i = a.begin(); i != a.end(); ++i){
       id.append((*i)->getId());
   }
   return id;
}

//restituisce una lista con i nomi delle build
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

//restituiscce in base al carattere un colore
QColor Controller::colorCompare(char c)
{
    if(c == '>'){return Qt::red;}
    if(c == '='){return Qt::blue;}
    if(c == '<'){return Qt::darkGreen;}
    return Qt::black;
}

//Fine public


//Inizio public slots

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
        if (id.toInt() > 7){
            col->remove(id.toInt());
            sortCodex(codex->getSortInd());
        }else{
            window->showMessage(QString("Default Object can't de deleted."));
        }
    }
}

//imposta la view quando si carica una build(anche quella di default)
void Controller::setWindowChar(){

    int idChar = tabs[activeTab]->getId();
    QString name = QString::fromStdString(col->getCharName(idChar));
    tabs[activeTab]->setBuildName(name);


    C<int> stats = col->getCharStats(idChar);
    QList<QString> statsQ;
    for (auto i = stats.begin(); i != stats.end(); ++i)
    {
        statsQ.append(QString::number(*i));
    }
    tabs[activeTab]->setStats(statsQ);


    DeepPtr<Weapon> w = col->getCharWeapon(idChar);
    int id = w->getId();
    tabs[activeTab]->setWeapon(id);


    C<DeepPtr<Armor>> a = col->getCharArmor(idChar);
    QList<int> ls;
    for (auto i = a.begin(); i != a.end(); ++i)
    {
        ls.append((*i)->getId());
    }
    tabs[activeTab]->setArmor(ls);


    prevId.clear();
    C<DeepPtr<Consumable>> inv = col->getCharCons(idChar);
    QList<int> x;
    for (auto i = inv.begin(); i != inv.end(); ++i)
    {
        x.append((*i)->getId());
        prevId.append((*i)->getId());
    }
    tabs[activeTab]->setItems(x);


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
    window->setTabName(s);
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

//aggiunge un tab alla lista del controller
void Controller::addTab(windowtabwidget *t)
{
    tabs.append(t);
}

//rimuove un tab dalla lista del controller
void Controller::deleteTab(int index)
{
    if((index-1) == activeTab){
        //cose
    }
    tabs.removeAt(index-1);
}

//cambia il numero salvato in memoria del tab attivo e refresha
void Controller::changeTab(int i)
{
    activeTab = i-1;
    if(activeTab >= 0){
        refreshTab();
    }else{
        refreshWindow();
    }
}

//Controlla se è aperta un tab ccon l'id dato
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

//ottimizza la build
void Controller::optimize()
{
    col->maxAtk(tabs[activeTab]->getId());
    col->maxDefense(tabs[activeTab]->getId(),"MAXIMIZE");
    refreshTab();
}

//restituisce la preview di una build (e si occupa del compare se è la seconda selezionata)
void Controller::getInfoChar(QListWidgetItem *)
{
    int index = window->getIndSelChar();
    C<std::string> s = col->getInfoChar(index);
    QList<QString> stats;
    for(auto i = s.begin();i != s.end(); ++i){
        stats.append(QString::fromStdString(*i));
    }
    if(!window->getCheckValue()){
        activeChar = index;
        window->refreshCompare(stats);
    }else{
        C<char> o = col->compareChara(activeChar,index);
        auto i = o.begin();
        window->clearCompare();
        window->setWithColor(("Name : " + stats[0]+"\n\n"),Qt::black);
        for(int j = 1;j < stats.length(); j++){
            window->setWithColor((stats[j]+"\n"),colorCompare((*i)));
            i++;
        }
    }
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
    codex = new Codex(this,getItemsNames("all",""),getItemsId("all",""));
    codex->exec();
}

//filtra la lista in Codex
void Controller::sortCodex(QVariant i)
{
    switch (i.toInt()) {
    case 0:
        codex->refreshCodex(getItemsNames("all","all"),getItemsId("all","all"));
        break;
    case 1:
        codex->refreshCodex(getItemsNames("Weapon","all"),getItemsId("Weapon","all"));
        break;
    case 2:
        codex->refreshCodex(getItemsNames("Weapon","Melee"),getItemsId("Weapon","Melee"));
        break;
    case 3:
        codex->refreshCodex(getItemsNames("Weapon","Ranged"),getItemsId("Weapon","Ranged"));
        break;
    case 4:
        codex->refreshCodex(getItemsNames("Armor","all"),getItemsId("Armor","all"));
        break;
    case 5:
        codex->refreshCodex(getItemsNames("Armor","HELM"),getItemsId("Armor","HELM"));
        break;
    case 6:
        codex->refreshCodex(getItemsNames("Armor","CHEST"),getItemsId("Armor","CHEST"));
        break;
    case 7:
        codex->refreshCodex(getItemsNames("Armor","GLOVES"),getItemsId("Armor","GLOVES"));
        break;
    case 8:
        codex->refreshCodex(getItemsNames("Armor","BOOTS"),getItemsId("Armor","BOOST"));
        break;
    case 10:
        codex->refreshCodex(getItemsNames("Consumable","all"),getItemsId("Consumable","all"));
        break;
    case 11:
        codex->refreshCodex(getItemsNames("Consumable","Buff"),getItemsId("Consumable","Buff"));
        break;
    case 12:
        codex->refreshCodex(getItemsNames("Consumable","Healing"),getItemsId("Consumable","Healing"));
        break;
    default:
        break;
    }

}

void Controller::importChar()  //per importare build
{
    try {
        QString path = window->importCharDialog();
        col->importChara(path.toStdString());
        refreshWindow();
    } catch (std::runtime_error exc) {
        std::cout<<"Error before importation"<<std::endl;

    }
}

void Controller::importObj()  //per importare oggetti
{
    try {
        QString path = codex->showImportDialog();
        col->importObj(path.toStdString());
        sortCodex(codex->getSortInd());
    } catch (std::runtime_error exc) {
        std::cout<<"Error before importation"<<std::endl;
    }

}

void Controller::exportChar()  //per esportare build
{
    try {
        QString path = window->exportCharDialog();
        col->exportChara(window->getIndSelChar(), path.toStdString());
    } catch (std::runtime_error exc) {
        std::cout<<"Error before exportation"<<std::endl;
    }

}

void Controller::exportObj()  //per esportare oggetti
{
    try {
        QString path = codex->showExpDialog();
        int id = codex->getSelectedItem()->data(Qt::UserRole).toInt();
        col->exportObj(id,path.toStdString());
    } catch (std::runtime_error exc) {
        std::cout<<"Error before exportation"<<std::endl;
    }

}


//crea un personaggio di default
void Controller::defaultChar()
{
    col->createDefaultChar();
    refreshWindow();
}

//Elimina un personaggio
void Controller::deleteChar()
{
    int ind = window->getIndSelChar();
    if (ind != 0){
        int i = -1;
        for (int j = 0; j < tabs.count(); j++)
        {
            int i2 = tabs[j]->getId();
            if(i2 == ind)
            {
                i = j;
            }else if (i2 > ind)
            {
                tabs[j]->setId(i2-1);
            }
        }
        if (i != -1)
        {
            window->closeTab(i+1);
        }
        col->deleteChar(ind);
        refreshWindow();
    }else{
        window->showMessage(QString("First build can't be deleted."));
    }
}

//Fine public slots


