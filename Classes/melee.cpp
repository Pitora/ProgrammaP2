#include "melee.h"

Melee::Melee(std::string a_t, unsigned int d, unsigned int p) : attack_type(a_t), durability(d), precision(p){}

Melee::Melee(std::string imported) : Weapon(imported){       
    if (imported.find("<Melee>") != -1 && imported.find("</Melee>") != -1)
    {
        size_t pos1 = imported.find("<AttackType>");
        size_t pos2 = imported.find("</AttackType>");
        std::string l = "<AttackType>";
        pos1 += l.length();
        attack_type = imported.substr(pos1, pos2 - pos1); //Attenzione : length legge bytes di lunghezza e quindi non sempre corrispondono

        pos1 = imported.find("<Durability>");
        pos2 = imported.find("</Durability>");
        l = "<Durability>";
        pos1 += l.length();
        durability = stoi(imported.substr(pos1, pos2 - pos1));

        pos1 = imported.find("<Precision>");
        pos2 = imported.find("</Precision>");
        l = "<Precision>";
        pos1 += l.length();
        precision = stoi(imported.substr(pos1, pos2 - pos1));

    }else{
        //throw .....
    }
} 

Melee::~Melee(){
    std::cout<<"Cancellata Melee"<<std::endl;
}

std::string Melee::exp() {       
    std::string s = "<Melee>";
    s += Weapon::exp();
    s += "<AttackType>" + attack_type + "</AttackType>";
    s += "<Durability>" + std::to_string(durability) + "</Durability>";
    s += "<Precision>" + std::to_string(precision) + "</Precision>";
    s += "</Melee>";
    return s;
}



