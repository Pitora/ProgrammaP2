#include <iostream>
#include <string>
#include "ranged.h"

using namespace std;

Ranged::Ranged(dList<DeepPtr<Magazine>> a, int rec, int rel) : eq_ammo(a), recoil(rec), reload_time(rel) {}

Ranged::Ranged(string imported) : weapon(imported){       
    if (imported.find("<Ranged>") != -1 && imported.find("</Ranged>") != -1)
    {
        size_t pos1 = imported.find("<A0>");
        size_t pos2 = imported.find("</A0>");
        int i = 0;
        string l;
        while (pos1 != -1 && pos2 != -1)
        {
            l = "<A" + i + ">";
            pos1 += l.length();
            string s = imported.substr(pos1, pos2 - pos1);
            Magazine m;
            Ammo a(s);
            DeepPtr<Ammo> a2(a);
            m.type = a2;
            pos1 = s.find("<Count>");
            pos2 = s.find("</Count>");
            l = "<Count>";
            pos1 += l.length();
            m.count = s.substr(pos1, pos2-pos1);
            DeepPtr<Magazine> m2(m);
            eq_ammo.insertBack(m2);
            i++;
            pos1 = imported.find("<A" + i + ">");
            pos2 = imported.find("</A" + i + ">");                      
        }

        pos1 = imported.find("<Recoil>");
        pos2 = imported.find("</Recoil>");
        l = "<Recoil>";
        pos1 += l.length();
        recoil = imported.substr(pos1, pos2 - pos1);

        pos1 = imported.find("<ReloadT>");
        pos2 = imported.find("</ReloadT>");
        l = "<ReloadT>";
        pos1 += l.length();
        reload_time = imported.substr(pos1, pos2 - pos1);


    }else{
        //throw .....
    }
} 

Ranged::~Ranged(){
    for (DeepPtr<Magazine> p : eq_ammo) {
        delete *(p).type;
        delete *(p).count;
        delete p;
    }

    delete recoil;
    delete reload_time;

}

virtual string Ranged::export() {       
    string s = "<Ranged>";
    s += Weapon::export();
    s += "<EqAmmo>";
    int i = 0;
    for(DeepPtr<Magazine> p : eq_ammo)
    {
        s += "<A" + i + ">";
        s += *(*(p).type).export(); 
        s += "<Count>" + count + "</Count>";
        s += "</A" + i + ">";
        i++;
    }
    s+= "</EqAmmo>";
    s += "<Recoil>" + recoil + "</Recoil>";
    s += "<ReloadT>" + reload_time + "</ReloadT>";
    s += "</Ranged>";
    return s;
}





