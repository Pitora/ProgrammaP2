#include "object.h"

Obj::Obj(){}

Obj::Obj(int i, std::string n) : id(i), name(n) {}

Obj::Obj(std::string imported){

    id = stoi(substring(imported, "<Id>", "</Id>"));

    name = substring(imported, "<Name>", "</Name>");
}

Obj::~Obj() {}


std::string Obj::exp() {       //Esempio di export?
    std::string s = "<Obj>";
    s += "<Id>" + std::to_string(id) + "</Id>";
    s += "<Name>" + name + "</Name>";
    s += "</Obj>";
    return s;
}

std::string Obj::substring(std::string s, std::string w1, std::string w2)
{
    size_t pos1 = s.find(w1);
    size_t pos2 = s.find(w2);
    pos1 += w1.length();        //attenzione : legge i bytes che compongono la stringa
    return s.substr(pos1,pos2-pos1);
}




