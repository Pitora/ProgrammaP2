#include "object.h"

Obj::Obj(){}

Obj::Obj(int i, std::string n) : id(i), name(n) {}

Obj::Obj(std::string imported){
    if (checkKW(imported, "<Obj>", "</Obj>"))
    {
        id = stoi(substring(imported, "<Id>", "</Id>"));
        name = substring(imported, "<Name>", "</Name>");
    }
    else throw err_import();
}

Obj::~Obj() {
    std::cout<<"Distruttore virtuale puro chiamato"<<std::endl;
}


std::string Obj::exp() const{       //Esempio di export?
    std::string s = "<Obj>";
    s += "<Id>" + std::to_string(id) + "</Id>";
    s += "<Name>" + name + "</Name>";
    s += "</Obj>";
    return s;
}

std::string Obj::getInfo() const{
    return "Id : " + std::to_string(id) + "\n" + "Nome : " + name + "\n";
}

std::string Obj::substring(std::string s, std::string w1, std::string w2)
{
    size_t pos1 = s.find(w1);
    size_t pos2 = s.find(w2);
    pos1 += w1.length();        //attenzione : legge i bytes che compongono la stringa
    if (pos1 <= pos2)
    {
        return s.substr(pos1,pos2-pos1);
    }
    else throw err_sub();
    
}

bool Obj::checkKW(std::string s, std::string kw1, std::string kw2)
{
    if (s.find(kw1) != size_t(-1) && s.find(kw2) != size_t(-1))
    {
        return true;
    }
    else return false;
}




std::ostream& operator<<(std::ostream& s, const Obj& o) {
        o.print(s);
        return s;
}




