#include "healing.h"

Healing::Healing(std::string a_v, unsigned int p) : affected_value(a_v), potency(p) {}

Healing::Healing(int i, std::string n, std::string a_v, unsigned int p) : Consumable(i,n), affected_value(a_v), potency(p) {}

Healing::Healing(std::string imported) : Consumable(imported){       
    if (sm::checkKW(imported, "<Healing>", "</Healing>"))
    {
        affected_value = sm::substring(imported, "<AffValue>", "</AffValue>" ); //Attenzione : length legge bytes di lunghezza e quindi non sempre corrispondono

        potency = stoi(sm::substring(imported, "<Potency>", "</Potency>"));

    }else throw err_import();
} 

Healing::~Healing() {
    std::cout<<"Cura cancellata"<<std::endl;
}

Healing* Healing::clone() const {return new Healing(*this);}

void Healing::print(std::ostream& os) const{
    Consumable::print(os);
    os<<"affected value : "<<affected_value<<std::endl;
    os<<"Potency : "<<potency<<std::endl;
}


std::string Healing::exp() const{       
    std::string s = "<Healing>";
    s += Consumable::exp();
    s += "<AffValue>" + affected_value + "</AffValue>";
    s += "<Potency>" + std::to_string(potency) + "</Potency>";
    s += "</Healing>";
    return s;
}


std::string Healing::getInfo() const{
    std::string s = Consumable::getInfo();
    s += "Affected value : " + affected_value + "\n";
    s += "Potency : " + std::to_string(potency) + "\n";
    return s;
}




