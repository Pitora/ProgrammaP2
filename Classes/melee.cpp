#include "melee.h"

Melee::Melee(std::string a_t, std::string a_e, unsigned int d) : attack_type(a_t), added_effect(a_e), durability(d) {}

Melee::Melee(int i, std::string n, int w, int c, int r, int rav, int cc, int s_str, int s_dex, int s_aim, std::string a_t, std::string a_e, unsigned int d) : Weapon(i,n,w,c,r,rav,cc,s_str,s_dex,s_aim), attack_type(a_t), added_effect(a_e), durability(d){}

Melee::Melee(std::string imported) : Weapon(imported){       
    if (imported.find("<Melee>") != -1 && imported.find("</Melee>") != -1)
    {
        attack_type = substring(imported,"<AttackType>","</AttackType>"); //Attenzione : length legge bytes di lunghezza e quindi non sempre corrispondono

        added_effect = stoi(substring(imported,"<AddEff>","</AddEff>"));

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
    os<<"Attack type : "<<attack_type<<std::endl;
    os<<"Added effect :"<<added_effect<<std::endl;
    os<<"Durability : "<<durability<<std::endl;   
}

std::string Melee::exp() const{       
    std::string s = "<Melee>";
    s += Weapon::exp();
    s += "<AttackType>" + attack_type + "</AttackType>";
    s += "<AddEff>" + added_effect + "</AddEff>";
    s += "<Durability>" + std::to_string(durability) + "</Durability>";
    //s += "<Precision>" + std::to_string(precision) + "</Precision>";
    s += "</Melee>";
    return s;
}



