#include "buff.h"


Buff::Buff(std::string e, unsigned int p, unsigned int d) : effect(e), percentage(p), duration(d) {}

Buff::Buff(int i, std::string n, std::string e, unsigned int p, unsigned int d) : Consumable(i,n), effect(e), percentage(p), duration(d) {}

Buff::Buff(std::string imported) : Consumable(imported){
    if (sm::checkKW(imported,"<Buff>","</Buff>"))
    {
        effect = sm::substring(imported, "<Effect>", "</Effect>"); //Attenzione : length legge bytes di lunghezza e quindi non sempre corrispondono

        percentage = stoi(sm::substring(imported,"<Percentage>", "</Percentage>"));

        duration = stoi(sm::substring(imported, "<Duration>", "</Duration>"));

    }else throw err_import();
} 

Buff::~Buff(){
    std::cout<<"Cancellato un buff"<<std::endl;
}

void Buff::print(std::ostream& os) const{
    Consumable::print(os);
    os<<"Effect : "<<effect<<std::endl;
    os<<"Percentage : "<<percentage<<std::endl;
    os<<"Duration : "<<duration<<std::endl;
}

std::string Buff::exp() const{
    std::string s = "<Buff>";
    s += Consumable::exp();
    s += "<Effect>" + effect + "</Effect>";
    s += "<Percentage>" + std::to_string(percentage) + "</Percentage>";
    s += "<Duration>" + std::to_string(duration) + "</Duration>";
    s += "</Buff>";
    return s;
}

std::string Buff::getInfo() const{
    std::string s = Consumable::getInfo();
    s += "Effect : " + effect + "\n";
    s += "Percentage : " + std::to_string(percentage) + "\n";
    s += "Duration : " + std::to_string(duration) + "\n";
    return s;
}




