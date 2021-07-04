#include "collection.h"

Collection::Collection(){
    std::string s = readFile("data.xml");
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
}

void Collection::initialize(){
    //caricare da un file esterno tutte le informazioni su list
}

void Collection::save(){
    
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
    }
}

void Collection::update(){

}

void Collection::add(){

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

bool Collection::checkCopy(DeepPtr<Obj>& o) const{
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
    while(i!= list.end() && !found)
    {
        ++i;
        if ((*i)->getId() == id)
        {
            found = true;
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
    }
    //else throw...    
}

void Collection::importChara(){

}

void Collection::exportChara(){

}
