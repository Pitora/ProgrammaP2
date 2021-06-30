#include <iostream>
#include <string>
#include "weapon.h"

using namespace std;

Weapon::Weapon(int w, int c, int r, int rav, int eav, int cc) : weight(w), cost(c), rarity(r), raw_attack_value(rav), elem_attack_value(eav), critical_chance(cc){}

Weapon::Weapon(string imported) : Object(imported){       //esempio di import?
    if (imported.find("<Weapon>") != -1 && imported.find("</Weapon>") != -1)
    {
        size_t pos1 = imported.find("<Weight>");
        size_t pos2 = imported.find("</Weight>");
        string l = "<Weight>";
        pos1 += s.length();
        weight = imported.substr(pos1 - pos1.length(), pos2 - pos1); //Attenzione : length legge bytes di lunghezza e quindi non sempre corrispondono

        pos1 = imported.find("<Cost>");
        pos2 = imported.find("</Cost>");
        string l = "<Cost>";
        pos1 += s.length();
        cost = imported.substr(pos1, pos2 - pos1);

        pos1 = imported.find("<Rarity>");
        pos2 = imported.find("</Rarity>");
        string l = "<Rarity>";
        pos1 += s.length();
        rarity = imported.substr(pos1, pos2 - pos1);

        pos1 = imported.find("<RawAttack>");
        pos2 = imported.find("</RawAttack>");
        string l = "<RawAttack>";
        pos1 += s.length();
        raw_attack_value = imported.substr(pos1, pos2 - pos1);

        pos1 = imported.find("<ElemAttack>");
        pos2 = imported.find("</ElemAttack>");
        string l = "<ElemAttack>";
        pos1 += s.length();
        elem_attack_value = imported.substr(pos1, pos2 - pos1);

        pos1 = imported.find("<CritChance>");
        pos2 = imported.find("</CritChance>");
        string l = "<CritChance>";
        pos1 += s.length();
        critical_chance = imported.substr(pos1, pos2 - pos1);


    }else{
        //throw .....
    }
} 

Weapon::~Weapon(){
    delete weight;
    delete cost;
    delete rarity;
    delete raw_attack_value;
    delete elem_attack_value;
    delete critical_chance;
}

virtual string Weapon::export() {       //Esempio di export?
    string s = "<Weapon>";
    s += Object::export();
    s += "<Weight>" + weight + "</Weight>";
    s += "<Cost>" + cost + "</Cost>";
    s += "<Rarity>" + rarity + "</Rarity>";
    s += "<RawAttack>" + raw_attack_value + "</RawAttack>";
    s += "<ElemAttack>" + elem_attack_value + "</ElemAttack>";
    s += "<CritChance>" + critical_chance + "</CritChance>";
    s += "</Weapon>";
    return s;
}




