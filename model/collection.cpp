#include "collection.h"

Collection::Collection() : list(), charas(), nextId(){       //costruttore standard, si occupa anche dell'apertura del file di salvataggio e popolazione lista
    try {
        std::string s = readFile("data.xml");
        if (s != ""){
            if (sm::checkKW(s , "<Data>","</Data>")){
                std::cout<<"Sto leggendo"<<std::endl;
                if (sm::checkKW(s, "<NextId>", "</NextId>"))
                {
                    nextId = std::stoi(sm::substring(s, "<NextId>", "</NextId>"));
                }
                int i = 0;
                while(sm::checkKW(s, "<Item" + std::to_string(i) + '>', "</Item" + std::to_string(i) + '>'))
                {
                    std::string item = sm::substring(s,"<Item" + std::to_string(i) +'>' ,"</Item" + std::to_string(i) +'>');
                    if (sm::checkKW(item, "<Melee>", "</Melee>"))
                    {   
                        list.insertBack(DeepPtr<Obj>(new Melee(item)));
                    }
                    else if (sm::checkKW(item, "<Ranged>", "</Ranged>"))
                    {
                        list.insertBack(DeepPtr<Obj>(new Ranged(item)));
                    }
                    else if (sm::checkKW(item, "<Armor>", "</Armor>"))
                    {
                        list.insertBack(DeepPtr<Obj>(new Armor(item)));
                    }
                    else if (sm::checkKW(item, "<Healing>", "</Healing>"))
                    {
                        list.insertBack(DeepPtr<Obj>(new Healing(item)));
                    }
                    else if (sm::checkKW(item, "<Buff>", "</Buff>"))
                    {
                        list.insertBack(DeepPtr<Obj>(new Buff(item)));
                    }
                    i++;
                }
                i = 0;
                while(sm::checkKW(s, "<Chara" + std::to_string(i) + '>', "</Chara" + std::to_string(i) + '>'))
                {
                    std::string chara = sm::substring(s,"<Chara" + std::to_string(i) +'>' ,"</Chara" + std::to_string(i) +'>');
                    charas.push_back(DeepPtr<Character>(new Character(chara)));
                    i++;
                }
                std::cout<<"Database letto"<<std::endl;
            }else throw err_file();
        }else{
            throw err_fileNotReadable();
        }
    }
    catch(err_file){std::cout<<"Il database non è corretto."<<std::endl;initialize();}
    catch(err_fileNotReadable) {std::cout<<"Il database non esiste."<<std::endl;initialize();}
    catch(err_import){std::cout<<"L'importazione non è andata a buon fine."<<std::endl; initialize();}
    catch(err_sub){std::cout<<"Substring ha fallito : valori mancanti."<<std::endl; initialize();}
    
}

Collection::~Collection(){
    //std::cout<<"Cancellazione collection"<<std::endl;
    try{
        save();
    }
    catch(err_fileNotCreated){std::cout<<"Non è stato possibile salvare il database"<<std::endl;}
}

//Metodo che si occupa di inizializzare collection(in caso di problemi, ricrea gli oggetti di default)
void Collection::initialize(){
    std::cout<<"Sono stati generati i valori default"<<std::endl;
    if (!checkId(0)){
        add("Broken Helm", "HELM", "NO EFFECT", 5, 50);
        add("Broken chest", "CHEST", "NO EFFECT", 10, 50);
        add("Broken gloves", "GLOVES", "NO EFFECT", 4, 50);
        add("Broken boots", "BOOTS", "NO EFFECT", 7, 50);
        add("Broken sword", 2, 100, 1, 10, 5, 1, 1, 1, "slash", "no effect", 500);
        add("Broken bow", 1, 100, 1, 0, 10, 1, 1, 2, 100, 5, 300);
        add("Bad apple", "ALL STATS UP", 1, 50);
        add("Broken glass of water", "HP", 1);
        nextId = 8;
        createDefaultChar();
    }
}

//Metodo che si occupa di salvare il contenuto di collection (meno il character)
void Collection::save() const{
    
    std::cout<<"Sto salvando...";
    std::string s = "<Data>";
    s += "<NextId>" + std::to_string(nextId) + "</NextId>";
    int i = 0;
    for (C<DeepPtr<Obj>>::const_iterator iter = list.begin(); iter != list.end(); ++iter )
    {
        s += "<Item" + std::to_string(i) + '>';
        s += (*iter)->exp();
        s += "</Item" + std::to_string(i) + '>';
        i++;
    }
    for(unsigned int j = 0; j < charas.size(); j++)
    {
        s += "<Chara" + std::to_string(j) + '>';
        s += charas[j]->exp();
        s += "</Chara" + std::to_string(j) + '>';
    }
    s += "</Data>";
    std::ofstream out("data.xml");
    if(out)
    {
        out<<"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"<<s;
        out.close();
        std::cout<<"Salvato!"<<std::endl;
    }else throw err_fileNotCreated();
}

//Metodo che ritorna il prossimo id utlizzabile e aumenta la variabile che ne tiene conto
int Collection::getNewId(){
    nextId++;
    return nextId-1;
}

//Metodo che, dati i valori di un pezzo d'armatura, aggiunge un pezzo di armatura alla lista con quei valori
void Collection::add(std::string n, std::string a_t, std::string r, int d_v, int d){
    int id = getNewId();
    list.insertBack(DeepPtr<Obj>(new Armor(id, n, a_t, r, d_v, d)));
}

//Metodo che, dati i valori di un arma melee, aggiunge un arma melee alla lista con quei valori
void Collection::add(std::string n, int w, int c, int r, int rav, int cc, int s_str, int s_dex, int s_aim, std::string a_t, std::string a_e, int d){
    int id = getNewId();
    list.insertBack(DeepPtr<Obj>(new Melee(id,n,w,c,r,rav,cc,s_str,s_dex,s_aim,a_t,a_e,d)));
}

//Metodo che, dati i valori di un arma ranged, aggiunge un arma ranged alla lista con quei valori
void Collection::add(std::string n, int w, int c, int r, int rav, int cc, int s_str, int s_dex, int s_aim, int rec, int rel, int m){
    int id = getNewId();
    list.insertBack(DeepPtr<Obj>(new Ranged(id,n,w,c,r,rav,cc,s_str,s_dex,s_aim,rec,rel,m)));
}

//Metodo che,dati i valori di un consumabile potenziante (Buff), aggiunge alla lista un buff con quei valori
void Collection::add(std::string n, std::string e, int p, int d){
    int id = getNewId();
    list.insertBack(DeepPtr<Obj>(new Buff(id,n,e,p,d)));
}

//Metodo che, dati i valori di un consumabile curativo (Healing), aggiunge alla lista un Healing con quei valori
void Collection::add(std::string n, std::string a_v, int p){
    int id = getNewId();
    list.insertBack(DeepPtr<Obj>(new Healing(id,n,a_v,p)));
}

//Metodo che, dato un id, ritorna un iteratore costante all'oggetto con quel id presente nella lista
C<DeepPtr<Obj>>::const_iterator Collection::getIter(int id) const{
    C<DeepPtr<Obj>>::const_iterator i = list.begin();
    bool found = false;

    while(i!= list.end() && !found)
    {
        if ((*i)->getId() == id)
        {
            found = true;
        }else{
            i++;
        }
    }
    return i;
}

//Metodo che, dato un id, rimuove dalla lista l'oggetto con quel id
void Collection::remove(int id){
    C<DeepPtr<Obj>>::const_iterator i = getIter(id);
    try {
        if (i != list.end() && id > 7)          //8 oggetti di default intoccabili
        {
            checkEq(id);
            list.remove(*i);
        }
    }catch(err_nodeNotFound){std::cout<<"Il nodo non esiste."<<std::endl;}


}

//Metodo che, dato un id, stampa in console il contenuto dell'oggetto con quel id
void Collection::show(int id) const{
    C<DeepPtr<Obj>>::const_iterator i = getIter(id);
    try{
        if (i != list.end())
        {
            std::cout<<*i<<std::endl;
        }
        else{
            throw err_notFound();
        }
    }
    catch(err_notFound){std::cout<<"L'oggetto non esiste"<<std::endl;}
}


//Metodo che dato una stringa che indica un tipo di oggetto, ritorna una lista con gli oggetti di list che sono di quel tipo
C<DeepPtr<Obj>> Collection::getObjPerType(std::string type, std::string type2 ) const{
    C<DeepPtr<Obj>> l;
    for (C<DeepPtr<Obj>>::const_iterator i = list.begin(); i != list.end(); ++i)
    {
        if (type == "Weapon" && dynamic_cast<Weapon*>(&(*(*i))))
        {
            l.insertBack(*i);
        }
        else if (type == "Consumable" && dynamic_cast<Consumable*>(&(*(*i))))
        {
            l.insertBack(*i);
        }
        else if (type == "Armor")
        {
            if (Armor* a = dynamic_cast<Armor*>(&(*(*i))))          
            {
                if (a->getArmorType() == type2)
                {
                    l.insertBack(*i);
                }
            }
        }
    }
    return l;
}


//Metodo che, dato un id, ritorna una stringa con tutte le informazioni dell'oggetto in lista con quel id
std::string Collection::getInfoObj(int id) const {
    C<DeepPtr<Obj>>::const_iterator i = getIter(id);
    if (i != list.end())
    {
        return (*i)->getInfo();
    }
    return "Placeholder : se sei qui, bravo, ti sei messo di impegno.";
}

//Metodo che ritorna tutta la lista costante (non usato)
const C<DeepPtr<Obj>> Collection::getAllObj() const{
    return list;
}



//Metodo che, dato un percorso di memoria a un file .xml, ritorna tutto il file .xml in stringa
std::string Collection::readFile(std::string filename)
{
    std::string file;
    std::ifstream in(filename, std::ios::in | std::ios::binary);
    if(in)
    {
        in.seekg(0, std::ios::end);
        file.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&file[0], file.size());
        in.close();
        return file;
    }
    else throw err_fileNotReadable();
}

//Metodo booleano che, dato un id, ritorna vero se tale id è già in uso, falso altrimenti
bool Collection::checkId(const int id) const{
    for (C<DeepPtr<Obj>>::const_iterator i = list.begin(); i != list.end(); ++i )
    {
        if ((*i)->getId() == id)
        {   
            return true;
        }
    }
    return false;
}


//Metodo che, dato un un percorso di memoria, si occupa dell'importazione di un oggetto
void Collection::importObj(std::string filename){
    try{
        std::string file = readFile(filename);
        if(sm::checkKW(file, "<Id>", "</Id>"))
        {
            int probId = stoi(sm::substring(file, "<Id>", "</Id>"));
            //std::cout<<probId<<std::endl;
            if(!checkId(probId)){

                if (sm::checkKW(file, "<Melee>", "</Melee>"))
                {   
                    list.insertBack(DeepPtr<Obj>(new Melee(file)));
                }
                else if (sm::checkKW(file, "<Ranged>", "</Ranged>"))
                {
                    list.insertBack(DeepPtr<Obj>(new Ranged(file)));
                }
                else if (sm::checkKW(file, "<Armor>", "</Armor>"))
                {
                    list.insertBack(DeepPtr<Obj>(new Armor(file)));
                }
                else if (sm::checkKW(file, "<Healing>", "</Healing>"))
                {
                    list.insertBack(DeepPtr<Obj>(new Healing(file)));
                }
                else if (sm::checkKW(file, "<Buff>", "</Buff>"))
                {
                    list.insertBack(DeepPtr<Obj>(new Buff(file)));
                }
                else{
                    throw err_file();
                }

            }else{
                throw err_notNew();
            }
        }else{
            throw err_file();
        }
    }
    catch(err_file){std::cout<<"Il file non è corretto"<<std::endl; }
    catch(err_fileNotReadable){std::cout<<"Il file non esiste"<<std::endl;}
    catch(err_import){std::cout<<"Il file non esiste"<<std::endl;}
    catch(err_notNew){std::cout<<"L'oggetto è già presente"<<std::endl; }
    catch(err_sub){std::cout<<"Substring ha fallito : valori mancanti"<<std::endl;}

}

//Metodo che, dato un percorso di memoria, si occupa dell'esportazione di un oggetto
void Collection::exportObj(int id, std::string filename){
    C<DeepPtr<Obj>>::const_iterator i = getIter(id);
    
    try {
        if (i != list.end())
        {
            std::string ex = (*i)->exp();
            std::ofstream out(filename+".xml");
            if(out)
            {
                out<<"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"<<ex;
                out.close();
            }
            else throw err_fileNotCreated();
        }else throw err_notFound();  
    } 
    catch(err_fileNotCreated){std::cout<<"Il file non è stato creato"<<std::endl;} 
    catch(err_notFound){std::cout<<"L'oggetto da esportare non esiste"<<std::endl;}

}

//Metodo che, dato un percorso di memoria, si occupa dell'importazione di un personaggio. Aggiunge in lista gli oggetti del character importato che non sono in lista.
void Collection::importChara(std::string filename){
    try{
        std::string file = readFile(filename);

        charas.push_back(DeepPtr<Character>( new Character(file)));

        DeepPtr<Weapon> w = charas[charas.size()-1]->getEqWeap();

        if(!checkId(w->getId()))
        {           
            if (Melee* m = dynamic_cast<Melee*>(&(*w)))
            {
                list.insertBack(DeepPtr<Obj>(new Melee(*m)));
            }
            else if (Ranged* b = dynamic_cast<Ranged*>(&(*w)))
            {
                list.insertBack(DeepPtr<Obj>(new Ranged(*b)));
            }
        }

        C<DeepPtr<Armor>> a = charas[charas.size()-1]->getEqArmor();
        for (C<DeepPtr<Armor>>::const_iterator i = a.begin(); i != a.end(); ++i)
        {
            if(!checkId((*i)->getId()))
            {
                list.insertBack(DeepPtr<Obj>(new Armor(*(*i))));
            }
        }

        C<DeepPtr<Consumable>> c = charas[charas.size()-1]->getInv();
        for (C<DeepPtr<Consumable>>::const_iterator i = c.begin(); i != c.end(); ++i)
        {
            if(!checkId((*i)->getId()))
            {
                if (Healing* h = dynamic_cast<Healing*>(&(*(*i))))
                {
                    list.insertBack(DeepPtr<Obj>(new Healing(*h)));
                }
                else if (Buff* b = dynamic_cast<Buff*>(&(*(*i))))
                {
                    list.insertBack(DeepPtr<Obj>(new Buff(*b)));
                }
            }
        }
    }
    catch(err_fileNotReadable){std::cout<<"Il file non esiste"<<std::endl;}
    catch(err_import){std::cout<<"L'importazione non è andata a buon fine"<<std::endl;}
    catch(err_sub) {std::cout<<"Substring ha fallito : valori mancanti"<<std::endl;}
    
}

//Metodo che, dato un percorso di memoria, si occupa dell'esportazione di un character
void Collection::exportChara(int i, std::string filename){
    std::string ex = charas[i]->exp();

    try{
        std::ofstream out(filename + ".xml");
        if (out)
        {
            out<<"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"<<ex;
            out.close();
        }
        else throw err_fileNotCreated();
    }
    catch(err_fileNotCreated){std::cout<<"Il file non è stato creato"<<std::endl;}
}

void Collection::createDefaultChar()
{
    charas.push_back(DeepPtr<Character> (new Character()));
    modifyCharName(charas.size() - 1 ,"Default build");
    modifyCharWeap(charas.size() - 1, 4);
    modifyCharArmor(charas.size() - 1,0,-1);
    modifyCharArmor(charas.size() - 1,1,-1);
    modifyCharArmor(charas.size() - 1,2,-1);
    modifyCharArmor(charas.size() - 1,3,-1);
    modifyCharInv(charas.size() - 1,6,-1);
    modifyCharInv(charas.size() - 1,6,-1);
    modifyCharInv(charas.size() - 1,6,-1);
    setCharAim(charas.size() - 1,15);
    setCharDex(charas.size() - 1,15);
    setCharStr(charas.size() - 1,15);
    setCharVit(charas.size() - 1,15);
}

//Metodo che elimina il chara scelto
void Collection::deleteChar(int i)
{
    if (i > 0)      //Non è possibile cancellare il primo chara
    {
        charas.erase(charas.begin() + i);
    }
}




//Metodo che, data ua stringa, modifica il nome del character
void Collection::modifyCharName(int i, std::string s){ charas[i]->setName(s);}

//Metodo che, dato un id, prende dalla lista l'oggetto con quel id e lo equipaggia al character
void Collection::modifyCharWeap(int i, int id){
    C<DeepPtr<Obj>>::const_iterator it = getIter(id);
    try {
        charas[i]->setWeap(*it);
    }
    catch(err_wrongType){std::cout<<"L'oggetto è di un tipo non consono"<<std::endl;}
}

//Metodo che, dati due id, rimuove dal character il pezzo d'armatura con il secondo id e equipaggia quello con il primo id
void Collection::modifyCharArmor(int i, int id1, int id2){
    try{
        if (id1 != id2){
                if (id2 != -1)
                {
                    removeCharEq(i, id2);
                }
                C<DeepPtr<Obj>>::const_iterator it = getIter(id1);
                charas[i]->addArmor(*it);
        }else throw err_sameObject();
    }
    catch(err_wrongType){std::cout<<"L'oggetto è di un tipo non consono"<<std::endl;}
    catch(err_notFound){std::cout<<"L'oggetto non esiste"<<std::endl;}
    catch(err_disequip){std::cout<<"L'oggetto non può essere rimosso perché non è uno di questi oggetti."<<std::endl;}
    catch(err_sameObject){std::cout<<"L'oggetto che si vuole rimuovere è lo stesso che si vuole aggiungere."<<std::endl;}
}

//Alternativo : Metodo che, dato un id, aggiunge il pezzo d'armatura in lista con quel id al character
void Collection::modifyCharArmorAlt(int i, int id)
{
    try{
        if (checkId(id) && !charas[i]->isRemovingEq(id))
        {
              C<DeepPtr<Obj>>::const_iterator it = getIter(id);
              charas[i]->changeArmorEq(*it);
        }else throw err_sameObject();
    }catch(err_sameObject){std::cout<<"L'oggetto è gia equipaggiato."<<std::endl;}
}


//Metodo che, dati due id, rimuove dal character il consumable con il secondo id e equipaggia quello con il primo id
void Collection::modifyCharInv(int i, int id1, int id2){
    try{
        if (id1 != id2){
            if (id2 != -1)
            {
                removeCharEq(i , id2);
            }
            C<DeepPtr<Obj>>::const_iterator it = getIter(id1);
            charas[i]->addConsum(*it);
        }else throw err_sameObject();
    }
    catch(err_wrongType){std::cout<<"L'oggetto è di un tipo non consono."<<std::endl;}
    catch(err_notFound){std::cout<<"L'oggetto non esiste."<<std::endl;}
    catch(err_disequip){std::cout<<"L'oggetto non può essere rimosso perché non è uno di questi oggetti."<<std::endl;}
    catch(err_sameObject){std::cout<<"L'oggetto che si vuole rimuovere è lo stesso che si vuole aggiungere."<<std::endl;}

}

//Metodo che, dato un id, rimuove dai pezzi equipaggiati del personaggio l'oggetto con quel id (No weapon, solo armor e consumable)
void Collection::removeCharEq(int i, int id){
    C<DeepPtr<Obj>>::const_iterator it = getIter(id);
    if ((it != list.end()) && (dynamic_cast<Healing*>(&(*(*it)))  ||  dynamic_cast<Buff*>(&(*(*it))) || dynamic_cast<Armor*>(&(*(*it)))))
    {
        charas[i]->disequip(*it);
    }else throw err_wrongType();
}

//Metodi per cambiare le statistiche al personaggio
void Collection::setCharVit(int i, int x){charas[i]->setVit(x);}
void Collection::setCharStr(int i, int x){charas[i]->setStr(x);}
void Collection::setCharDex(int i, int x){charas[i]->setDex(x);}
void Collection::setCharAim(int i, int x){charas[i]->setAim(x);}


//metodo che, dato l'id di un oggetto che sta per essere rimosso, se è equipaggiato, riequipaggia l'equipaggiamento di default al suo posto
void Collection::checkEq(int id){
    for (unsigned int i = 0; i < charas.size(); i++)
    {
        if (charas[i]->isRemovingEq(id))
        {
            C<DeepPtr<Obj>>::const_iterator it = getIter(id);
            if (dynamic_cast<Weapon*>(&(*(*it))))
            {
                modifyCharWeap(i,4);
            }
            else if (dynamic_cast<Consumable*>(&(*(*it))))
            {
                modifyCharInv(i,7,id);
            }
            else if (Armor* a = dynamic_cast<Armor*>(&(*(*it))))
            {
                if(a->getArmorType() == "HELM")
                {
                    modifyCharArmor(i,0,id);
                }
                else if(a->getArmorType() == "CHEST")
                {
                    modifyCharArmor(i,1,id);
                }
                else if(a->getArmorType() == "GLOVES")
                {
                    modifyCharArmor(i,2, id);
                }
                else if(a->getArmorType() == "BOOTS")
                {
                    modifyCharArmor(i,3,id);
                }

            }
        }
    }
}

void Collection::maxAtk(int i)
{
    DeepPtr<Weapon> w = charas[i]->getEqWeap();
    int str = charas[i]->getStr();
    int dex = charas[i]->getDex();
    int aim = charas[i]->getAim();
    int max = w->calcAttack(str, dex, aim);
    for(C<DeepPtr<Obj>>::const_iterator it = list.begin(); it != list.end(); it++)
    {
        if (Weapon* w2 = dynamic_cast<Weapon*>(&(*(*it))))
        {
            if (max < w2->calcAttack(str,dex,aim))
            {
                charas[i]->setWeap(*it);
                max = w2->calcAttack(str,dex,aim);
            }
        }
    }
}

void Collection::maxDefense(int i)
{
    C<DeepPtr<Armor>> eqA = charas[i]->getEqArmor();
    int p1,p2,p3,p4;
    p1 = p2 = p3 = p4 = -1;
    for (C<DeepPtr<Obj>>::const_iterator it = list.begin(); it != list.end(); it++) //possibile modifica : interazione diretta con il character piuttosto del metodo secondario
    {
        if (Armor* a = dynamic_cast<Armor*>(&(*(*it))))
        {
            if(a->getArmorType() == "HELM" && p1 < a->getDefense())
            {
                modifyCharArmorAlt(i, a->getId());
                p1 = a->getDefense();
            }
            else if (a->getArmorType() == "CHEST" && p2 < a->getDefense())
            {
                modifyCharArmorAlt(i, a->getId());
                p2 = a->getDefense();
            }
            else if(a->getArmorType() == "GLOVES" && p3 < a->getDefense())
            {
                modifyCharArmorAlt(i, a->getId());
                p3 = a->getDefense();
            }
            else if(a->getArmorType() == "BOOTS" &&  p4 < a->getDefense())
            {
                modifyCharArmorAlt(i, a->getId());
                p4 = a->getDefense();
            }
        }
    }
}





const C<std::string> Collection::getCharsName() const
{
    C<std::string> l;
    for (unsigned int i = 0; i < charas.size(); i++)
    {
        l.insertBack(charas[i]->getName());
    }
    return l;
}



//Metodi vari per ottenere informazioni di uno specifico character
const std::string Collection::getCharName(int i) const {return charas[i]->getName();}
const C<int> Collection::getCharStats(int i) const { return charas[i]->getStats();}
const DeepPtr<Weapon> Collection::getCharWeapon(int i) const {return charas[i]->getEqWeap();}
const C<DeepPtr<Armor>> Collection::getCharArmor(int i)const {return charas[i]->getEqArmor();}
const C<DeepPtr<Consumable>> Collection::getCharCons(int i) const {return charas[i]->getInv();}
int Collection::getCharAtk(int i) const {return charas[i]->damage();}
int Collection::getCharDef(int i) const {return charas[i]->defense();}
const DeepPtr<Character> Collection::getChar(int i) const {return charas[i];}





