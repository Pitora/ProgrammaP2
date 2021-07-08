#include "healing.h"

Healing::Healing(std::string a_v, unsigned int p) : affected_value(a_v), potency(p) {}

Healing::Healing(int i, std::string n, std::string a_v, unsigned int p) : Consumable(i,n), affected_value(a_v), potency(p) {}

Healing::Healing(std::string imported) : Consumable(imported){       
    if (imported.find("<Healing>") != -1 && imported.find("</Healing>") != -1)
    {
        affected_value = substring(imported, "<AffValue>", "</AffValue>" ); //Attenzione : length legge bytes di lunghezza e quindi non sempre corrispondono

        potency = stoi(substring(imported, "<Potency>", "</Potency>"));

    }else{
        //throw .....
    }
} 

Healing::~Healing() {
    std::cout<<"Cura cancellata"<<std::endl;
}

void Healing::print(std::ostream& os){
    Consumable::print(os);
    os<<"affected value : "<<affected_value<<std::endl;
    os<<"Potency : "<<potency<<std::endl;
}


std::string Healing::exp() {       
    std::string s = "<Healing>";
    s += Consumable::exp();
    s += "<AffValue>" + affected_value + "</AffValue>";
    s += "<Potency>" + std::to_string(potency) + "</Potency>";
    s += "</Healing>";
    return s;
}




