#include "melee.h"

Melee::Melee(std::string a_t, unsigned int d, unsigned int p) : attack_type(a_t), durability(d) {}

Melee::Melee(std::string imported) : Weapon(imported){       
    if (imported.find("<Melee>") != -1 && imported.find("</Melee>") != -1)
    {
        attack_type = substring(imported,"<AttackType>","</AttackType>"); //Attenzione : length legge bytes di lunghezza e quindi non sempre corrispondono

        durability = stoi(substring(imported,"<Durability>","</Durability>"));

        //precision = stoi(substring(imported,"<Precision>","</Precision>"));

    }else{
        //throw .....
    }
} 

Melee::~Melee(){
    std::cout<<"Cancellata Melee"<<std::endl;
}


void Melee::print(std::ostream& os){
    Weapon::print(os);
    os<<"Attack_type : "<<attack_type<<std::endl;
    os<<"Reload time : "<<durability<<std::endl;
}

std::string Melee::exp() {       
    std::string s = "<Melee>";
    s += Weapon::exp();
    s += "<AttackType>" + attack_type + "</AttackType>";
    s += "<Durability>" + std::to_string(durability) + "</Durability>";
    //s += "<Precision>" + std::to_string(precision) + "</Precision>";
    s += "</Melee>";
    return s;
}



