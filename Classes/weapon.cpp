#include "weapon.h"

Weapon::Weapon(){}

Weapon::Weapon(int w, int c, int r, int rav, int eav, int cc) : weight(w), cost(c), rarity(r), raw_attack_value(rav), elem_attack_value(eav), critical_chance(cc){}

Weapon::Weapon(std::string imported) : Obj(imported){       //esempio di import?
    if (imported.find("<Weapon>") != -1 && imported.find("</Weapon>") != -1)
    {
        size_t pos1 = imported.find("<Weight>");
        size_t pos2 = imported.find("</Weight>");
        std::string l = "<Weight>";
        pos1 += l.length();
        weight = stoi(imported.substr(pos1, pos2 - pos1)); //Attenzione : length legge bytes di lunghezza e quindi non sempre corrispondono

        pos1 = imported.find("<Cost>");
        pos2 = imported.find("</Cost>");
        l = "<Cost>";
        pos1 += l.length();
        cost = stoi(imported.substr(pos1, pos2 - pos1));

        pos1 = imported.find("<Rarity>");
        pos2 = imported.find("</Rarity>");
        l = "<Rarity>";
        pos1 += l.length();
        rarity = stoi(imported.substr(pos1, pos2 - pos1));

        pos1 = imported.find("<RawAttack>");
        pos2 = imported.find("</RawAttack>");
        l = "<RawAttack>";
        pos1 += l.length();
        raw_attack_value = stoi(imported.substr(pos1, pos2 - pos1));

        pos1 = imported.find("<ElemAttack>");
        pos2 = imported.find("</ElemAttack>");
        l = "<ElemAttack>";
        pos1 += l.length();
        elem_attack_value = stoi(imported.substr(pos1, pos2 - pos1));

        pos1 = imported.find("<CritChance>");
        pos2 = imported.find("</CritChance>");
        l = "<CritChance>";
        pos1 += l.length();
        critical_chance = stoi(imported.substr(pos1, pos2 - pos1));


    }else{
        //throw .....
    }
} 

Weapon::~Weapon(){
    std::cout<<"Cancellata arma"<<std::endl;
}

std::string Weapon::exp() {       //Esempio di export?
    std::string s = "<Weapon>";
    s += Obj::exp();
    s += "<Weight>" + std::to_string(weight) + "</Weight>";
    s += "<Cost>" + std::to_string(cost) + "</Cost>";
    s += "<Rarity>" + std::to_string(rarity) + "</Rarity>";
    s += "<RawAttack>" + std::to_string(raw_attack_value) + "</RawAttack>";
    s += "<ElemAttack>" + std::to_string(elem_attack_value) + "</ElemAttack>";
    s += "<CritChance>" + std::to_string(critical_chance) + "</CritChance>";
    s += "</Weapon>";
    return s;
}




