#include "collection.h"

Collection::Collection() : list(){
    std::string s = readFile("data.xml");
    if (s != ""){
        std::cout<<"Sto leggendo"<<std::endl;
        int i = 0;
        while(s.find("<Item" + std::to_string(i) + '>') != -1)
        {
            std::string item = Obj::substring(s,"<Item" + std::to_string(i) +'>' ,"</Item" + std::to_string(i) +'>');
            if (item.find("<Melee>") != -1)
            {   
                list.insertBack(DeepPtr<Obj>(new Melee(item)));
            }
            else if (item.find("<Ranged>") != -1)
            {
                list.insertBack(DeepPtr<Obj>(new Ranged(item)));
            }
            else if (item.find("<Armor>") != -1)
            {
                list.insertBack(DeepPtr<Obj>(new Armor(item)));
            }
            else if (item.find("<Healing>") != -1)
            {
                list.insertBack(DeepPtr<Obj>(new Healing(item)));
            }
            else if (item.find("<Buff>") != -1)
            {
                list.insertBack(DeepPtr<Obj>(new Buff(item)));
            }
            i++;
        }
        std::cout<<"Database letto"<<std::endl;
    }else{
        std::cout<<"Database non presente"<<std::endl;
    }
}

Collection::~Collection(){
    std::cout<<"Cancellazione collection"<<std::endl;
    save();
}

void Collection::save(){
    
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
    }else{
        std::cout<<"salvataggio non effettuato"<<std::endl;
    }
}

int Collection::generateId(){
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

bool Collection::remove(int id){
    C<DeepPtr<Obj>>::const_iterator i = getIter(id);

    if (i != list.end())
    {
        list.remove(*i);
        return true;
    }

    return false;
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
    //else throw...
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



bool Collection::importObj(std::string filename){
    
    std::string file = readFile(filename);
    if(file.find("<Id>") != -1)
    {
        int probId = stoi(Obj::substring(file, "<Id>", "</Id>"));
        //std::cout<<probId<<std::endl;
        if(!checkId(probId)){

            if (file.find("<Melee>") != -1)
            {   
                list.insertBack(DeepPtr<Obj>(new Melee(file)));
            }
            else if (file.find("<Ranged>") != -1)
            {
                list.insertBack(DeepPtr<Obj>(new Ranged(file)));
            }
            else if (file.find("<Armor>") != -1)
            {
                list.insertBack(DeepPtr<Obj>(new Armor(file)));
            }
            else if (file.find("<Healing>") != -1)
            {
                list.insertBack(DeepPtr<Obj>(new Healing(file)));
            }
            else if (file.find("<Buff>") != -1)
            {
                list.insertBack(DeepPtr<Obj>(new Buff(file)));
            }
            else{
                return false;
            }
            return true;
            
        }else{
            std::cout<<"Oggetto con lo stesso Id già esistente"<<std::endl;
            return false;
        }
    }else{
        std::cout<<"File non idoneo"<<std::endl;
        return false;
    }

}

void Collection::exportObj(int id, std::string filename){
    C<DeepPtr<Obj>>::const_iterator i = getIter(id);
    

    std::cout<<"Tentativo di esportazione"<<std::endl;

    if (i != list.end())
    {
        std::string ex = (*i)->exp();
        std::ofstream out(filename);
        if(out)
        {
            out<<"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"<<ex;
            out.close();
        }
        //else throw...
    }else{
        std::cout<<"Oggetto inesistente"<<std::endl;
    }
    //else throw...    
}

void Collection::importChara(std::string filename){
    std::string file = readFile(filename);

    chara = Character(file);

    DeepPtr<Weapon> w = chara.getEqWeap();
    if(!checkId(w->getId()))
    {
        list.insertBack(DeepPtr<Obj>(w->clone()));
    }

    //stessa cosa per armor e inventory

    C<DeepPtr<Armor>> a = chara.getEqArmor();
    for (C<DeepPtr<Armor>>::const_iterator i = a.begin(); i != a.end(); ++i)
    {
        if(!checkId((*i)->getId()))
        {
            list.insertBack(DeepPtr<Obj>((*i)->clone()));
        }
    }

    C<DeepPtr<Consumable>> c = chara.getInv();
    for (C<DeepPtr<Consumable>>::const_iterator i = c.begin(); i != c.end(); ++i)
    {
        if(!checkId((*i)->getId()))
        {
            list.insertBack(DeepPtr<Obj>((*i)->clone()));
        }
    }
    
}

void Collection::exportChara(std::string filename){
    std::string ex = chara.exp();
    std::ofstream out(filename);
    if (out)
    {
        out<<"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"<<ex;
        out.close();
    }
    //else throw...
}

void Collection::show(int id){
    C<DeepPtr<Obj>>::const_iterator i = list.begin();
    bool found = false;
    while(i != list.end() && !found)
    {
        if ((*i)->getId() == id)
        {
            found = true;
        }else{
            i++;
        }
    }

    if (found)
    {
        std::cout<<*i<<std::endl;
    }
    else{
        std::cout<<"Oggetto non trovato"<<std::endl;
    }
}

void Collection::modifyCharName(std::string s){ chara.setName(s);}

void Collection::modifyCharEq(int id1, int id2){
    C<DeepPtr<Obj>>::const_iterator i1 = getIter(id1);
    C<DeepPtr<Obj>>::const_iterator i2 = getIter(id2);
    
    if (i1 != list.end()){
        if (Weapon* w = dynamic_cast<Weapon*>(&(*(*i1))))
        {
            chara.setWeap(DeepPtr<Weapon>(new Weapon(*w)));
        }
        else if (Armor* a = dynamic_cast<Armor*>(&(*(*i1))))
        {
            if(i2 != list.end())
            {
                Armor* a2 = dynamic_cast<Armor*>(&(*(*i2)));
                chara.moveArmor(DeepPtr<Armor>(new Armor(*a)), DeepPtr<Armor>(new Armor(*a2)));
            }else{
                chara.moveArmor(DeepPtr<Armor>(new Armor(*a)), DeepPtr<Armor>(new Armor(0, "fake", "","",0,0)));
            }
        }
        else if (Consumable* c = dynamic_cast<Consumable*>(&(*(*i1))))
        {
            if(i2 != list.end())
            {
                Consumable* c2 = dynamic_cast<Consumable*>(&(*(*i2)));
                chara.moveConsum(DeepPtr<Consumable>(new Consumable(*c)), DeepPtr<Consumable>(new Consumable(*c2)));
            }else{
                chara.moveConsum(DeepPtr<Consumable>(new Consumable(*c)), DeepPtr<Consumable>(new Consumable(0, "fake")));
            }
        }    
    }else if(i2 != list.end()){
        if (Armor* a = dynamic_cast<Armor*>(&(*(*i2))))
        {
            chara.moveArmor(DeepPtr<Armor>(new Armor(0, "fake", "","",0,0)), DeepPtr<Armor>(new Armor(*a)));
        }
        else if (Consumable* a = dynamic_cast<Consumable*>(&(*(*i2))))
        {
            chara.moveConsum(DeepPtr<Consumable>(new Consumable(0, "fake")), DeepPtr<Consumable>(new Consumable(*a)));
        }
    }else{
        //throw...
    }
    
}


