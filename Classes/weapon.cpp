#include "weapon.h"

Weapon::Weapon(){}

Weapon::Weapon(int w, int c, int r, int rav, int cc, int s_str, int s_dex, int s_aim) : weight(w), cost(c), rarity(r), raw_attack_value(rav), critical_chance(cc), scaling_str(s_str), scaling_dex(s_dex), scaling_aim(s_aim){}

Weapon::Weapon(int i, std::string n, int w, int c, int r, int rav, int cc, int s_str, int s_dex, int s_aim) : Obj(i,n), weight(w), cost(c), rarity(r), raw_attack_value(rav), critical_chance(cc), scaling_str(s_str), scaling_dex(s_dex), scaling_aim(s_aim){}

Weapon::Weapon(std::string imported) : Obj(imported){     
    if (imported.find("<Weapon>") != -1 && imported.find("</Weapon>") != -1)
    {
        weight = stoi(substring(imported,"<Weight>","</Weight>")); 

        cost = stoi(substring(imported, "<Cost>", "</Cost>"));

        rarity = stoi(substring(imported, "<Rarity>", "</Rarity>"));

        raw_attack_value = stoi(substring(imported, "<RawAttack>", "</RawAttack>"));

        //elem_attack_value = stoi(substring(imported, "<ElemAttack>", "</ElemAttack>"));

        critical_chance = stoi(substring(imported, "<CritChance>", "</CritChance>"));

        scaling_str = stoi(substring(imported, "<ScStr>", "</ScStr>"));

        scaling_dex = stoi(substring(imported, "<ScDex>", "</ScDex>"));

        scaling_aim = stoi(substring(imported, "<ScAim>", "</ScAim>"));


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

void Weapon::print(std::ostream& os) const{
    Obj::print(os);
    os<<"Weight : "<<weight<<std::endl;
    os<<"Cost : "<<cost<<std::endl;
    os<<"Rarity : "<<rarity<<std::endl;
    os<<"Raw attack : "<<raw_attack_value<<std::endl;
    //os<<"Da sostituire : "<<elem_attack_value<<std::endl;
    os<<"Critical chance : "<<critical_chance<<std::endl;
    os<<"Scaling Strength : "<<scaling_str<<std::endl;
    os<<"Scaling Dex : "<<scaling_dex<<std::endl;
    os<<"Scaling Aim : "<<scaling_aim<<std::endl;
}

std::string Weapon::exp() const{     
    std::string s = "<Weapon>";
    s += Obj::exp();
    s += "<Weight>" + std::to_string(weight) + "</Weight>";
    s += "<Cost>" + std::to_string(cost) + "</Cost>";
    s += "<Rarity>" + std::to_string(rarity) + "</Rarity>";
    s += "<RawAttack>" + std::to_string(raw_attack_value) + "</RawAttack>";
    //s += "<ElemAttack>" + std::to_string(elem_attack_value) + "</ElemAttack>";
    s += "<CritChance>" + std::to_string(critical_chance) + "</CritChance>";
    s += "<ScStr>" + std::to_string(scaling_str) + "</ScStr>";
    s += "<ScDex>" + std::to_string(scaling_dex) + "</ScDex>";
    s += "<ScAim>" + std::to_string(scaling_aim) + "</ScAim>";
    s += "</Weapon>";
    return s;
}




