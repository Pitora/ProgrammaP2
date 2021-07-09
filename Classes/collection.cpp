#include "collection.h"

Collection::Collection(){
    std::string s = readFile("data.xml");
    if (s != ""){
        std::cout<<"Sto leggendo"<<std::endl;
        int i = 0;
        while(s.find("<Item" + std::to_string(i) + '>'))
        {
            std::string item = Obj::substring(s,"<Item" + std::to_string(i) +'>' ,"</Item" + std::to_string(i) +'>');
            if (item.find("<Melee>") != -1)
            {   
                Melee m(item);
                DeepPtr<Obj> o2(&m);
                list.insertBack(o2);
            }
            else if (item.find("<Ranged>") != -1)
            {
                Ranged r(item);
                DeepPtr<Obj> o2(&r);
                list.insertBack(o2);
            }
            else if (item.find("<Armor>") != -1)
            {
                Armor a(item);
                DeepPtr<Obj> o2(&a);
                list.insertBack(o2);
            }
            else if (item.find("<Healing>") != -1)
            {
                Healing h(item);
                DeepPtr<Obj> o2(&h);
                list.insertBack(o2);
            }
            else if (item.find("<Buff>") != -1)
            {
                Buff b(item);
                DeepPtr<Obj> o2(&b);
                list.insertBack(o2);
            }
            i++;
        }
    }else{
        std::cout<<"Database non presente"<<std::endl;
    }
}

void Collection::initialize(){
    //caricare da un file esterno tutte le informazioni su list
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

void Collection::update(){

}

void Collection::add(std::string n, std::string a_t, std::string r, int d_v, int d){
    Armor* a = new Armor(0, n, a_t, r, d_v, d);
    std::cout<<"Creata armatura"<<std::endl;
    list.insertBack(a);
    std::cout<<"Inserita armatura"<<std::endl;
}

void Collection::add(std::string n, int w, int c, int r, int rav, int cc, int s_str, int s_dex, int s_aim, std::string a_t, std::string a_e, int d){
    list.insertBack(DeepPtr<Obj>(new Melee(0,n,w,c,r,rav,cc,s_str,s_dex,s_aim,a_t,a_e,d)));
}

void Collection::add(std::string n, int w, int c, int r, int rav, int cc, int s_str, int s_dex, int s_aim, int rec, int rel, int m){
    list.insertBack(DeepPtr<Obj>(new Ranged(0,n,w,c,r,rav,cc,s_str,s_dex,s_aim,rec,rel,m)));
}

void Collection::add(std::string n, std::string e, int p, int d){
    list.insertBack(DeepPtr<Obj>(new Buff(0,n,e,p,d)));
}

void Collection::add(std::string n, std::string a_v, int p){
    list.insertBack(DeepPtr<Obj>(new Healing(0,n,a_v,p)));
}

void Collection::remove(int id){
    // creato metodo remove in tc.cpp (template di c) per la rimozione remove(DeepPtr....)
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

bool Collection::checkCopy(const DeepPtr<Obj>& o) const{
    for (C<DeepPtr<Obj>>::const_iterator i = list.begin(); i != list.end(); ++i )
    {
        if (*(*i) == *o)
        {   
            return true;
        }
        return false;
    }
}



bool Collection::importObj(std::string filename){
    
    std::string file = readFile(filename);

    DeepPtr<Obj> o;

    if (file.find("<Melee>") != -1)
    {   
        Melee m(file);
        DeepPtr<Obj> o2(&m);
        o = o2;
    }
    else if (file.find("<Ranged>") != -1)
    {
        Ranged r(file);
        DeepPtr<Obj> o2(&r);
        o = o2;
    }
    else if (file.find("<Armor>") != -1)
    {
        Armor a(file);
        DeepPtr<Obj> o2(&a);
        o = o2;
    }
    else if (file.find("<Healing>") != -1)
    {
        Healing h(file);
        DeepPtr<Obj> o2(&h);
        o = o2;
    }
    else if (file.find("<Buff>") != -1)
    {
        Buff b(file);
        DeepPtr<Obj> o2(&b);
        o = o2;
    }
    else{
        return false;
    }

    if(!(checkCopy(o)))   
    {
        list.insertBack(o);
        return true;
    }

    return true;

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
