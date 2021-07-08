#include "ranged.h"


Ranged::Ranged(int rec, int rel, int m) : recoil(rec), reload_time(rel), magazine(m) {}

Ranged::Ranged(int i, std::string n, int w, int c, int r, int rav, int cc, int s_str, int s_dex, int s_aim, int rec, int rel, int m) : Weapon(i,n,w,c,r,rav,cc,s_str,s_dex,s_aim), recoil(rec), reload_time(rel), magazine(m) {}

Ranged::Ranged(std::string imported) : Weapon(imported){       
    if (imported.find("<Ranged>") != -1 && imported.find("</Ranged>") != -1)
    {
        recoil = stoi(substring(imported,"<Recoil>","</Recoil>"));

        reload_time = stoi(substring(imported,"<ReloadT>","</ReloadT>"));

        magazine = stoi(substring(imported,"<Magazine>","</Magazine>"));

    }else{
        //throw .....
    }
} 

Ranged::~Ranged(){
    std::cout<<"Cancellata Ranged"<<std::endl;
}

void Ranged::print(std::ostream& os){
    Weapon::print(os);
    os<<"Recoil : "<<recoil<<std::endl;
    os<<"Reload time : "<<reload_time<<std::endl;
    os<<"Magazine : "<<magazine<<std::endl;
}

std::string Ranged::exp() {       
    std::string s = "<Ranged>";
    s += Weapon::exp();
    s += "<Recoil>" + std::to_string(recoil) + "</Recoil>";
    s += "<ReloadT>" + std::to_string(reload_time) + "</ReloadT>";
    s += "<Magazine>" + std::to_string(magazine) + "</Magazine>";
    s += "</Ranged>";
    return s;
}





