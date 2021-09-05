#include "ranged.h"


Ranged::Ranged(int rec, int rel, int m) : recoil(rec), reload_time(rel), magazine(m) {}

Ranged::Ranged(int i, std::string n, int w, int c, int r, int rav, int cc, int s_str, int s_dex, int s_aim, int rec, int rel, int m) : Weapon(i,n,w,c,r,rav,cc,s_str,s_dex,s_aim), recoil(rec), reload_time(rel), magazine(m) {}

Ranged::Ranged(std::string imported) : Weapon(imported){
    if (sm::checkKW(imported, "<Ranged>", "</Ranged>"))
    {
        recoil = stoi(sm::substring(imported,"<Recoil>","</Recoil>"));

        reload_time = stoi(sm::substring(imported,"<ReloadT>","</ReloadT>"));

        magazine = stoi(sm::substring(imported,"<Magazine>","</Magazine>"));

    }else{
        throw err_import();
    }
} 

Ranged::~Ranged(){
    //std::cout<<"Cancellata Ranged"<<std::endl;
}

Ranged* Ranged::clone() const {return new Ranged(*this);}

void Ranged::print(std::ostream& os) const{
    Weapon::print(os);
    os<<"Recoil : "<<recoil<<std::endl;
    os<<"Reload time : "<<reload_time<<std::endl;
    os<<"Magazine : "<<magazine<<std::endl;
}

std::string Ranged::exp() const{       
    std::string s = "<Ranged>";
    s += Weapon::exp();
    s += "<Recoil>" + std::to_string(recoil) + "</Recoil>";
    s += "<ReloadT>" + std::to_string(reload_time) + "</ReloadT>";
    s += "<Magazine>" + std::to_string(magazine) + "</Magazine>";
    s += "</Ranged>";
    return s;
}

std::string Ranged::getInfo() const{
    std::string s = Weapon::getInfo();
    s += "Recoil : " + std::to_string(recoil) + "\n";
    s += "Reload time : " + std::to_string(reload_time) + "\n";
    s += "Magazine : " + std::to_string(magazine) + "\n";
    return s;
}

int Ranged::calcAttack(int cStr, int cDex, int cAim) const
{
    int scaleSum = (cStr*getScalingStr()/10)*(cStr/getScalingStr())+(cDex*getScalingDex()/10)*(cDex/getScalingDex())+(cAim*getScalingAim()/5)*(cAim/getScalingAim());
    return (getAttack()+scaleSum);
}





