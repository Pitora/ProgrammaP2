#include "ranged.h"


Ranged::Ranged(dList<DeepPtr<Magazine>> a, int rec, int rel) : eq_ammo(a), recoil(rec), reload_time(rel) {}

Ranged::Ranged(std::string imported) : Weapon(imported), eq_ammo(){       
    if (imported.find("<Ranged>") != -1 && imported.find("</Ranged>") != -1)
    {
        size_t pos1 = imported.find("<A0>");
        size_t pos2 = imported.find("</A0>");
        int i = 0;
        std::string l;
        while (pos1 != -1 && pos2 != -1)
        {
            l = "<A" + std::to_string(i) + ">";
            pos1 += l.length();
            std::string s = imported.substr(pos1, pos2 - pos1);
            Magazine m;
            Ammo a(s);
            DeepPtr<Ammo> a2(&a);
            m.type = a2;
            pos1 = s.find("<Count>");
            pos2 = s.find("</Count>");
            l = "<Count>";
            pos1 += l.length();
            m.count = stoi(s.substr(pos1, pos2-pos1));
            DeepPtr<Magazine> m2(&m);
            eq_ammo.insertBack(m2);
            i++;
            pos1 = imported.find("<A" + std::to_string(i) + ">");
            pos2 = imported.find("</A" + std::to_string(i) + ">");                      
        }

        pos1 = imported.find("<Recoil>");
        pos2 = imported.find("</Recoil>");
        l = "<Recoil>";
        pos1 += l.length();
        recoil = stoi(imported.substr(pos1, pos2 - pos1));

        pos1 = imported.find("<ReloadT>");
        pos2 = imported.find("</ReloadT>");
        l = "<ReloadT>";
        pos1 += l.length();
        reload_time = stoi(imported.substr(pos1, pos2 - pos1));


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
    s += "<EqAmmo>";
    int i = 0;
    for(DeepPtr<Magazine> p : eq_ammo)
    {
        s += "<A" + std::to_string(i) + ">";
        s += (*((*p).type)).exp(); 
        s += "<Count>" + std::to_string((*p).count) + "</Count>";
        s += "</A" + std::to_string(i) + ">";
        i++;
    }
    s+= "</EqAmmo>";
    s += "<Recoil>" + std::to_string(recoil) + "</Recoil>";
    s += "<ReloadT>" + std::to_string(reload_time) + "</ReloadT>";
    s += "</Ranged>";
    return s;
}





