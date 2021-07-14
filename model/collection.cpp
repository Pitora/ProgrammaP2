#include "collection.h"

Collection::Collection() : list(), chara(){
    try {
        std::string s = readFile("data.xml");
        if (s != ""){
            if (sm::checkKW(s , "<Data>","</Data>")){
                std::cout<<"Sto leggendo"<<std::endl;
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
                std::cout<<"Database letto"<<std::endl;
                initialize();
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
    std::cout<<"Cancellazione collection"<<std::endl;
    try{
        save();
    }
    catch(err_fileNotCreated){std::cout<<"Non è stato possibile salvare il database"<<std::endl;}
}

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
    }
    chara = DeepPtr<Character>(new Character());
    modifyCharName("Default build");
    modifyCharWeap(4);
    modifyCharArmor(0,-1);
    modifyCharArmor(1,-1);
    modifyCharArmor(2,-1);
    modifyCharArmor(3,-1);
    modifyCharInv(6,-1);
    modifyCharInv(6,-1);
    modifyCharInv(6,-1);
    setCharAim(15);
    setCharDex(15);
    setCharStr(15);
    setCharVit(15);
}

void Collection::save() const{
    
    std::cout<<"Sto salvando...";
    std::string s = "<Data>";
    int i = 0;
    for (C<DeepPtr<Obj>>::const_iterator iter = list.begin(); iter != list.end(); ++iter )
    {
        s += "<Item" + std::to_string(i) + '>';
        s += (*iter)->exp();
        s += "</Item" + std::to_string(i) + '>';
        i++;
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

int Collection::generateId() const{
    int max = -1;
    for (C<DeepPtr<Obj>>::const_iterator i = list.begin(); i != list.end(); ++i)
    {
        if ((*i)->getId()>max)
        {
            max = (*i)->getId();
        }  
    }
    return max+1;
}

void Collection::add(std::string n, std::string a_t, std::string r, int d_v, int d){
    int id = generateId();
    list.insertBack(DeepPtr<Obj>(new Armor(id, n, a_t, r, d_v, d)));
}

void Collection::add(std::string n, int w, int c, int r, int rav, int cc, int s_str, int s_dex, int s_aim, std::string a_t, std::string a_e, int d){
    int id = generateId();
    list.insertBack(DeepPtr<Obj>(new Melee(id,n,w,c,r,rav,cc,s_str,s_dex,s_aim,a_t,a_e,d)));
}

void Collection::add(std::string n, int w, int c, int r, int rav, int cc, int s_str, int s_dex, int s_aim, int rec, int rel, int m){
    int id = generateId();
    list.insertBack(DeepPtr<Obj>(new Ranged(id,n,w,c,r,rav,cc,s_str,s_dex,s_aim,rec,rel,m)));
}

void Collection::add(std::string n, std::string e, int p, int d){
    int id = generateId();
    list.insertBack(DeepPtr<Obj>(new Buff(id,n,e,p,d)));
}

void Collection::add(std::string n, std::string a_v, int p){
    int id = generateId();
    list.insertBack(DeepPtr<Obj>(new Healing(id,n,a_v,p)));
}

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

void Collection::remove(int id){
    C<DeepPtr<Obj>>::const_iterator i = getIter(id);
    try {
        if (i != list.end() && id > 7)          //7 oggetti di default intoccabili
        {
            checkEq(id);
            list.remove(*i);
        }
    }catch(err_nodeNotFound){std::cout<<"Il nodo non esiste."<<std::endl;}


}

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

C<DeepPtr<Obj>> Collection::getObjPerType(std::string type, std::string type2 ) const{
    C<DeepPtr<Obj>> l;
    for (C<DeepPtr<Obj>>::const_iterator i = list.begin(); i != list.end(); ++i)
    {
        if (type == "Weapon" && dynamic_cast<Weapon*>(&(*(*i))))    //Ampliabile
        {
            l.insertBack(*i);
        }
        else if (type == "Consumable" && dynamic_cast<Consumable*>(&(*(*i))))   //Ampliabile
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

std::string Collection::getInfoObj(int id) const {
    C<DeepPtr<Obj>>::const_iterator i = getIter(id);
    if (i != list.end())
    {
        return (*i)->getInfo();
    }
    return "Placeholder : se sei qui, bravo.";
}

const C<DeepPtr<Obj>> Collection::getAllObj() const{
    return list;
}




std::string Collection::readFile(std::string filename)          //ritorna tutto il file sottoforma di stringa
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



bool Collection::importObj(std::string filename){
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
                    return false;
                }
                return true;
                
            }else{
                throw err_notNew();
                return false;
            }
        }else{
            throw err_file();
            return false;
        }
    }
    catch(err_file){std::cout<<"Il file non è corretto"<<std::endl; return false;}
    catch(err_fileNotReadable){std::cout<<"Il file non esiste"<<std::endl;}
    catch(err_import){std::cout<<"Il file non esiste"<<std::endl;}
    catch(err_notNew){std::cout<<"L'oggetto è già presente"<<std::endl; return false;}
    catch(err_sub){std::cout<<"Substring ha fallito : valori mancanti"<<std::endl;}

}

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

void Collection::importChara(std::string filename){
    try{
        std::string file = readFile(filename);

        chara = DeepPtr<Character>( new Character(file));

        DeepPtr<Weapon> w = chara->getEqWeap();
        std::cout<<w<<std::endl;
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

        C<DeepPtr<Armor>> a = chara->getEqArmor();
        for (C<DeepPtr<Armor>>::const_iterator i = a.begin(); i != a.end(); ++i)
        {
            if(!checkId((*i)->getId()))
            {
                list.insertBack(DeepPtr<Obj>(new Armor(*(*i))));
            }
        }

        C<DeepPtr<Consumable>> c = chara->getInv();
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

void Collection::exportChara(std::string filename){
    std::string ex = chara->exp();

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



void Collection::modifyCharName(std::string s){ chara->setName(s);}

void Collection::modifyCharWeap(int id){
    C<DeepPtr<Obj>>::const_iterator i = getIter(id);
    try {
        chara->setWeap(*i);
    }
    catch(err_wrongType){std::cout<<"L'oggetto è di un tipo non consono"<<std::endl;}
}

void Collection::modifyCharArmor(int id1, int id2){
    try{
        if (id1 != id2){
                if (id2 != -1)
                {
                    removeCharEq(id2);
                }
                C<DeepPtr<Obj>>::const_iterator i = getIter(id1);
                chara->addArmor(*i);
        }else throw err_sameObject();
    }
    catch(err_wrongType){std::cout<<"L'oggetto è di un tipo non consono"<<std::endl;}
    catch(err_notFound){std::cout<<"L'oggetto non esiste"<<std::endl;}
    catch(err_disequip){std::cout<<"L'oggetto non può essere rimosso perché non è uno di questi oggetti."<<std::endl;}
    catch(err_sameObject){std::cout<<"L'oggetto che si vuole rimuovere è lo stesso che si vuole aggiungere."<<std::endl;}
}

void Collection::modifyCharArmorAlt(int id)//metodo per chiamare la versione alternativa del metodo che cambia l'armatura, (usa solo l'id)
{
    try{
        if (checkId(id) && !chara->isRemovingEq(id))
        {
              C<DeepPtr<Obj>>::const_iterator i = getIter(id);
              chara->changeArmorEq(*i);
        }else throw err_sameObject();
    }catch(err_sameObject){std::cout<<"L'oggetto è gia equipaggiato."<<std::endl;}
}

void Collection::modifyCharInv(int id1, int id2){
    try{
        if (id1 != id2){
            if (id2 != -1)
            {
                removeCharEq(id2);
            }
            C<DeepPtr<Obj>>::const_iterator i = getIter(id1);
            chara->addConsum(*i);
        }else throw err_sameObject();
    }
    catch(err_wrongType){std::cout<<"L'oggetto è di un tipo non consono."<<std::endl;}
    catch(err_notFound){std::cout<<"L'oggetto non esiste."<<std::endl;}
    catch(err_disequip){std::cout<<"L'oggetto non può essere rimosso perché non è uno di questi oggetti."<<std::endl;}
    catch(err_sameObject){std::cout<<"L'oggetto che si vuole rimuovere è lo stesso che si vuole aggiungere."<<std::endl;}

}

void Collection::removeCharEq(int id){
    C<DeepPtr<Obj>>::const_iterator i = getIter(id);
    if ((i != list.end()) && (dynamic_cast<Healing*>(&(*(*i)))  ||  dynamic_cast<Buff*>(&(*(*i))) || dynamic_cast<Armor*>(&(*(*i)))))
    {
        chara->disequip(*i);
    }else throw err_wrongType();
}

void Collection::setCharVit(int x){chara->setVit(x);}
void Collection::setCharStr(int x){chara->setStr(x);}
void Collection::setCharDex(int x){chara->setDex(x);}
void Collection::setCharAim(int x){chara->setAim(x);}

void Collection::checkEq(int id){ //metodo che reimposta l'equipaggiamento di default in caso di cancellazione
    if (chara->isRemovingEq(id))
    {
        C<DeepPtr<Obj>>::const_iterator i = getIter(id);
        if (dynamic_cast<Weapon*>(&(*(*i))))
        {
            modifyCharWeap(4);
        }
        else if (dynamic_cast<Consumable*>(&(*(*i))))
        {
            modifyCharInv(7,id);
        }
        else if (Armor* a = dynamic_cast<Armor*>(&(*(*i))))
        {
            if(a->getArmorType() == "HELM")
            {
                modifyCharArmor(0,id);
            }
            else if(a->getArmorType() == "CHEST")
            {
                modifyCharArmor(1,id);
            }
            else if(a->getArmorType() == "GLOVES")
            {
                modifyCharArmor(2, id);
            }
            else if(a->getArmorType() == "BOOTS")
            {
                modifyCharArmor(3,id);
            }

        }
    }
}






std::string Collection::getCharName() const {return chara->getName();}
C<int> Collection::getCharStats() const { return chara->getStats();}
DeepPtr<Weapon> Collection::getCharWeapon() const {return chara->getEqWeap();}
C<DeepPtr<Armor>> Collection::getCharArmor()const {return chara->getEqArmor();}
C<DeepPtr<Consumable>> Collection::getCharCons() const {return chara->getInv();}
int Collection::getCharAtk() const {return chara->damage();}
int Collection::getCharDef() const {return chara->defense();}
const DeepPtr<Character> Collection::getChar() const {return chara;}





