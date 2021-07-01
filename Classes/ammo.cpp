#include "ammo.h"


Ammo::Ammo(std::string a_t, int a_v) : attack_type(a_t), attack_value(a_v) {}

Ammo::Ammo(std::string imported) : Consumable(imported){       
    if (imported.find("<Ammo>") != -1 && imported.find("</Ammo>") != -1)
    {
        size_t pos1 = imported.find("<AttackType>");
        size_t pos2 = imported.find("</AttackType>");
        std::string l = "<AttackType>";
        pos1 += l.length();
        attack_type = imported.substr(pos1, pos2 - pos1); //Attenzione : length legge bytes di lunghezza e quindi non sempre corrispondono

        pos1 = imported.find("<AttackValue>");
        pos2 = imported.find("</AttackValue>");
        l = "<AttackValue>";
        pos1 += l.length();
        attack_value = stoi(imported.substr(pos1, pos2 - pos1));


    }else{
        //throw .....
    }
} 


Ammo::~Ammo() { 
    std::cout<<"Ammo distrutte"<<std::endl;
};

std::string Ammo::exp() {       
    std::string s = "<Ammo>";
    s += Consumable::exp();
    s += "<AttackType>" + attack_type + "</AttackType>";
    s += "<AttackValue>" + std::to_string(attack_value) + "</AttackValue>";
    s += "</Ammo>";
    return s;
}



