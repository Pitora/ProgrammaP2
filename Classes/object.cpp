#include "object.h"

Obj::Obj(){}

Obj::Obj(int i, std::string n) : id(i), name(n) {}

Obj::Obj(std::string imported){
    size_t pos1 = imported.find("<Id>");
    size_t pos2 = imported.find("</Id>");
    std::string s = "<Id>";
    pos1 += s.length();
    id = stoi(imported.substr(pos1,pos2-pos1));

    pos1 = imported.find("<Name>");
    pos2 = imported.find("</Name>");
    s = "<Name>";
    pos1 += s.length();
    name = imported.substr(pos1, pos2-pos1);
}

Obj::~Obj() {}


std::string Obj::exp() {       //Esempio di export?
    std::string s = "<Object>";
    s += "<Id>" + std::to_string(id) + "</Id>";
    s += "<Name>" + name + "</Name>";
    s += "</Object>";
    return s;
}




