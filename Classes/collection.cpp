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
    //DeepPtr<Obj>* x = new DeepPtr<Obj>(new Armor(0, n, a_t, r, d_v, d));
    //std::cout<<"Creata armatura"<<std::endl;
    int id = generateId();
    list.insertBack(DeepPtr<Obj>(new Armor(id, n, a_t, r, d_v, d)));
    //std::cout<<"Inserita armatura"<<std::endl;
    //delete x;
}

void Collection::add(std::string n, int w, int c, int r, int rav, int cc, int s_str, int s_dex, int s_aim, std::string a_t, std::string a_e, int d){
    //DeepPtr<Obj>* x = new DeepPtr<Obj>(new Melee(0,n,w,c,r,rav,cc,s_str,s_dex,s_aim,a_t,a_e,d));
    int id = generateId();
    list.insertBack(DeepPtr<Obj>(new Melee(id,n,w,c,r,rav,cc,s_str,s_dex,s_aim,a_t,a_e,d)));
}

void Collection::add(std::string n, int w, int c, int r, int rav, int cc, int s_str, int s_dex, int s_aim, int rec, int rel, int m){
    //DeepPtr<Obj>* x = new DeepPtr<Obj>(new Ranged(0,n,w,c,r,rav,cc,s_str,s_dex,s_aim,rec,rel,m));
    int id = generateId();
    list.insertBack(DeepPtr<Obj>(new Ranged(id,n,w,c,r,rav,cc,s_str,s_dex,s_aim,rec,rel,m)));
}

void Collection::add(std::string n, std::string e, int p, int d){
    //DeepPtr<Obj>* x = new DeepPtr<Obj>(new Buff(0,n,e,p,d));
    int id = generateId();
    list.insertBack(DeepPtr<Obj>(new Buff(id,n,e,p,d)));
}

void Collection::add(std::string n, std::string a_v, int p){
    //DeepPtr<Obj>* x = new DeepPtr<Obj>(new Healing(0,n,a_v,p));
    int id = generateId();
    list.insertBack(DeepPtr<Obj>(new Healing(id,n,a_v,p)));
}

bool Collection::remove(int id){
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
        list.remove(*i);
    }

    return found;
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
    C<DeepPtr<Obj>>::const_iterator i = list.begin();
    bool found = false;

    std::cout<<"Tentativo di esportazione"<<std::endl;

    while(i!= list.end() && !found)
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

void Collection::importChara(){

}

void Collection::exportChara(){

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
