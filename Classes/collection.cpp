#include "collection.h"

Collection::Collection(){

}

void Collection::initialize(){
    //caricare da un file esterno tutte le informazioni su list
}

void Collection::save(){
    //salvare su un file esterno tutte le informazioni su list
}

void Collection::update(){

}

void Collection::add(){

}

void Collection::remove(int i){

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
        DeepPtr<Obj> o2(dynamic_cast<Obj*>(&m));
        o = o2;
    }
    else if (file.find("<Ranged>") != -1)
    {
        Ranged r(file);
        DeepPtr<Obj> o2(dynamic_cast<Obj*>(&r));
        o = o2;
    }
    else if (file.find("<Armor>") != -1)
    {
        Armor a(file);
        DeepPtr<Obj> o2(dynamic_cast<Obj*>(&a));
        o = o2;
    }
    else if (file.find("<Healing>") != -1)
    {
        Healing h(file);
        DeepPtr<Obj> o2(dynamic_cast<Obj*>(&h));
        o = o2;
    }
    else if (file.find("<Buff>") != -1)
    {
        Buff b(file);
        DeepPtr<Obj> o2(dynamic_cast<Obj*>(&b));
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
