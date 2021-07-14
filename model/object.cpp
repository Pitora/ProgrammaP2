#include "object.h"

Obj::Obj(){}

Obj::Obj(int i, std::string n) : id(i), name(n) {}

Obj::Obj(std::string imported){
    if (sm::checkKW(imported, "<Obj>", "</Obj>"))
    {
        id = stoi(sm::substring(imported, "<Id>", "</Id>"));
        name = sm::substring(imported, "<Name>", "</Name>");
    }
    else throw err_import();
}

Obj::~Obj() {
    //std::cout<<"Distruttore virtuale puro chiamato"<<std::endl;
}

bool Obj::operator== (const Obj& x) const {return id == x.id;}

std::ostream& operator<<(std::ostream& s, const Obj& o) {
        o.print(s);
        return s;
}


std::string Obj::exp() const{       //Esempio di export?
    std::string s = "<Obj>";
    s += "<Id>" + std::to_string(id) + "</Id>";
    s += "<Name>" + name + "</Name>";
    s += "</Obj>";
    return s;
}

void Obj::print(std::ostream& os) const {os<<"Id : "<<(*this).id<<" Nome : "<<(*this).name<<std::endl;}

std::string Obj::getInfo() const{
    return "Id : " + std::to_string(id) + "\n" + "Nome : " + name + "\n";
}


int Obj::getId() const {return id;}

std::string Obj::getName() const {return name;}




