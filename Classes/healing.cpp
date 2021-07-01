#include "healing.h"

Healing::Healing(std::string a_v, unsigned int p) : affected_value(a_v), potency(p) {}

Healing::Healing(std::string imported) : Consumable(imported){       
    if (imported.find("<Healing>") != -1 && imported.find("</Healing>") != -1)
    {
        size_t pos1 = imported.find("<AffValue>");
        size_t pos2 = imported.find("</AffValue>");
        std::string l = "<AffValue>";
        pos1 += l.length();
        affected_value = imported.substr(pos1, pos2 - pos1); //Attenzione : length legge bytes di lunghezza e quindi non sempre corrispondono

        pos1 = imported.find("<Potency>");
        pos2 = imported.find("</Potency>");
        l = "<Potency>";
        pos1 += l.length();
        potency = stoi(imported.substr(pos1, pos2 - pos1));

    }else{
        //throw .....
    }
} 

Healing::~Healing() {
    std::cout<<"Cura cancellata"<<std::endl;
}


std::string Healing::exp() {       
    std::string s = "<Healing>";
    s += Consumable::exp();
    s += "<AffValue>" + affected_value + "</AffValue>";
    s += "<Potency>" + std::to_string(potency) + "</Potency>";
    s += "</Healing>";
    return s;
}




