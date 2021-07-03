#include "ranged.h"


Ranged::Ranged(int rec, int rel, int m) : recoil(rec), reload_time(rel), magazine(m) {}

Ranged::Ranged(std::string imported) : Weapon(imported){       
    if (imported.find("<Ranged>") != -1 && imported.find("</Ranged>") != -1)
    {
        size_t pos1 = imported.find("<Recoil>");
        size_t pos2 = imported.find("</Recoil>");
        std::string l = "<Recoil>";
        pos1 += l.length();
        recoil = stoi(imported.substr(pos1, pos2 - pos1));

        pos1 = imported.find("<ReloadT>");
        pos2 = imported.find("</ReloadT>");
        l = "<ReloadT>";
        pos1 += l.length();
        reload_time = stoi(imported.substr(pos1, pos2 - pos1));

        pos1 = imported.find("<Magazine>");
        pos2 = imported.find("</Magazine>");
        l = "<Magazine>";
        pos1 += l.length();
        magazine = stoi(imported.substr(pos1, pos2 - pos1));



    }else{
        //throw .....
    }
} 

Ranged::~Ranged(){
    std::cout<<"Cancellata Ranged"<<std::endl;
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





