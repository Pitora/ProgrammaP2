#include <iostream>
#include <string>
#include "healing.h"

using namespace std;

Healing::Healing(string a_v, unsigned int p) : affected_value(a_v), potency(p) {}

Healing::Healing(string imported) : Consumable(imported){       
    if (imported.find("<Healing>") != -1 && imported.find("</Healing>") != -1)
    {
        size_t pos1 = imported.find("<AffValue>");
        size_t pos2 = imported.find("</AffValue>");
        string l = "<AffValue>";
        pos1 += l.length();
        affected_value = imported.substr(pos1, pos2 - pos1); //Attenzione : length legge bytes di lunghezza e quindi non sempre corrispondono

        pos1 = imported.find("<Potency>");
        pos2 = imported.find("</Potency>");
        string l = "<Potency>";
        pos1 += l.length();
        potency = imported.substr(pos1, pos2 - pos1);

    }else{
        //throw .....
    }
} 

Healing::~Healing() {
    delete affected_value;
    delete potency;
}


virtual string Healing::export() {       
    string s = "<Healing>";
    s += Consumable::export();
    s += "<AffValue>" + affected_value + "</AffValue>";
    s += "<Potency>" + potency + "</Potency>";
    s += "</Healing>";
    return s;
}




