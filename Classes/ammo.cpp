#include <iostream>
#include <string>
#include "ammo.h"

using namespace std;

Ammo(string a_t, int a_v) : attack_type(a_t), attack_value(a_v) {}

Ammo::Ammo(string imported) : Consumable(imported){       
    if (imported.find("<Ammo>") != -1 && imported.find("</Ammo>") != -1)
    {
        size_t pos1 = imported.find("<AttackType>");
        size_t pos2 = imported.find("</AttackType>");
        string l = "<AttackType>";
        pos1 += l.length();
        attack_type = imported.substr(pos1, pos2 - pos1); //Attenzione : length legge bytes di lunghezza e quindi non sempre corrispondono

        pos1 = imported.find("<AttackValue>");
        pos2 = imported.find("</AttackValue>");
        string l = "<AttackValue>";
        pos1 += l.length();
        attack_value = imported.substr(pos1, pos2 - pos1);


    }else{
        //throw .....
    }
} 


~Ammo() { 
    delete attack_type;
    delete attack_value;
};

virtual string Ammo::export() {       
    string s = "<Ammo>";
    s += Consumable::export();
    s += "<AttackType>" + attack_type + "</AttackType>";
    s += "<AttackValue>" + attack_value + "</AttackValue>";
    s += "</Ammo>";
    return s;
}



