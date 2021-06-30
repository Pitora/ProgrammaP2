#include <iostream>
#include <string>
#include "melee.h"

using namespace std;

Melee::Melee(string a_t, unsigned int d, unsigned int p) : attack_type(a_t), durability(d), precision(p){}

Melee::Melee(string imported) : Object(imported){       
    if (imported.find("<Melee>") != -1 && imported.find("</Melee>") != -1)
    {
        size_t pos1 = imported.find("<AttackType>");
        size_t pos2 = imported.find("</AttackType>");
        string l = "<AttackType>";
        pos1 += l.length();
        attack_type = imported.substr(pos1, pos2 - pos1); //Attenzione : length legge bytes di lunghezza e quindi non sempre corrispondono

        pos1 = imported.find("<Durability>");
        pos2 = imported.find("</Durability>");
        string l = "<Durability>";
        pos1 += l.length();
        durability = imported.substr(pos1, pos2 - pos1);

        pos1 = imported.find("<Precision>");
        pos2 = imported.find("</Precision>");
        string l = "<Precision>";
        pos1 += l.length();
        precision = imported.substr(pos1, pos2 - pos1);

    }else{
        //throw .....
    }
} 

Melee::~Melee(){
    delete attack_type;
    delete durability;
    delete precision;
}

virtual string Melee::export() {       
    string s = "<Melee>";
    s += Weapon::export();
    s += "<AttackType>" + attack_type + "</AttackType>";
    s += "<Durability>" + durability + "</Durability>";
    s += "<Precision>" + precision + "</Precision>";
    s += "</Melee>";
    return s;
}



