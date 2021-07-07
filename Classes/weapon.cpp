#include "weapon.h"

Weapon::Weapon(){}

Weapon::Weapon(int w, int c, int r, int rav, int eav, int cc) : weight(w), cost(c), rarity(r), raw_attack_value(rav), elem_attack_value(eav), critical_chance(cc){}

Weapon::Weapon(std::string imported) : Obj(imported){     
    if (imported.find("<Weapon>") != -1 && imported.find("</Weapon>") != -1)
    {
        weight = stoi(substring(imported,"<Weight>","</Weight>")); 

        cost = stoi(substring(imported, "<Cost>", "</Cost>"));

        rarity = stoi(substring(imported, "<Rarity>", "</Rarity>"));

        raw_attack_value = stoi(substring(imported, "<RawAttack>", "</RawAttack>"));

        elem_attack_value = stoi(substring(imported, "<ElemAttack>", "</ElemAttack>"));

        critical_chance = stoi(substring(imported, "<CritChance>", "</CritChance>"));


    }else{
        //throw .....
    }
} 

int Weapon::getAttack() const {return raw_attack_value;}
int Weapon::getScalingStr() const {return scaling_str;}
int Weapon::getScalingDex() const {return scaling_dex;}
int Weapon::getScalingAim() const {return scaling_aim;}

Weapon::~Weapon(){
    std::cout<<"Cancellata arma"<<std::endl;
}

void Weapon::print(std::ostream& os){
    Obj::print(os);
    os<<"Weight : "<<weight<<std::endl;
    os<<"Cost : "<<cost<<std::endl;
    os<<"Rarity : "<<rarity<<std::endl;
    os<<"Raw attack : "<<raw_attack_value<<std::endl;
    os<<"Da sostituire : "<<elem_attack_value<<std::endl;
    os<<"Critical chance : "<<critical_chance<<std::endl;
}

std::string Weapon::exp() {     
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




