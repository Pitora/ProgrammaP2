#include "melee.h"

Melee::Melee(std::string a_t, std::string a_e, unsigned int d) : attack_type(a_t), added_effect(a_e), durability(d) {}

Melee::Melee(int i, std::string n, int w, int c, int r, int rav, int cc, int s_str, int s_dex, int s_aim, std::string a_t, std::string a_e, unsigned int d) : Weapon(i,n,w,c,r,rav,cc,s_str,s_dex,s_aim), attack_type(a_t), added_effect(a_e), durability(d){}

Melee::Melee(std::string imported) : Weapon(imported){       
    if (sm::checkKW(imported, "<Melee>", "</Melee>"))
    {
        attack_type = sm::substring(imported,"<AttackType>","</AttackType>"); //Attenzione : length legge bytes di lunghezza e quindi non sempre corrispondono
        added_effect = sm::substring(imported,"<AddEff>","</AddEff>");
        durability = stoi(sm::substring(imported,"<Durability>","</Durability>"));

        //precision = stoi(substring(imported,"<Precision>","</Precision>"));

    }else{
        throw err_import();
    }
} 

Melee::~Melee(){
    //std::cout<<"Cancellata Melee"<<std::endl;
}

Melee* Melee::clone() const {return new Melee(*this);}

void Melee::print(std::ostream& os) const{
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
    s += "</Melee>";
    return s;
}

std::string Melee::getInfo() const{
    std::string s = Weapon::getInfo();
    s += "Attack type : " + attack_type + "\n";
    s += "Added effect : " + added_effect + "\n";
    s += "Durability : " + std::to_string(durability) + "\n";
    return s;
}

int Melee::calcAttack(int cStr, int cDex, int cAim) const
{
    int scaleSum;
    if(getWeight() > 60){
        scaleSum = cStr*getScalingStr()+(cDex*getScalingDex()/10) + (cAim*getScalingAim()/10);
        scaleSum = scaleSum-(((100-getWeight())/10)*scaleSum)/100;
    }else{
        scaleSum = (cStr*getScalingStr()/10) + (cDex*getScalingDex()) + (cAim*getScalingAim()/10);
        scaleSum = scaleSum+(((getWeight())/10)+scaleSum)/100;
    }

    if (added_effect != "NO EFFECT")
    {
        scaleSum = scaleSum - (scaleSum*12/100);
    }

    if(scaleSum < 0){scaleSum = 0;}
    return (getAttack()+scaleSum);
}



