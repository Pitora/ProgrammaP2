#include <iostream>
#include <string>
#include "buff.h"

using namespace std;

Buff::Buff(string e, unsigned int p, unsigned int d) : effect(e), percentage(p), duration(d) {}

Buff::Buff(string imported) : Consumable(imported){       
    if (imported.find("<Buff>") != -1 && imported.find("</Buff>") != -1)
    {
        size_t pos1 = imported.find("<Effect>");
        size_t pos2 = imported.find("</Effect>");
        string l = "<Effect>";
        pos1 += l.length();
        effect = imported.substr(pos1, pos2 - pos1); //Attenzione : length legge bytes di lunghezza e quindi non sempre corrispondono

        pos1 = imported.find("<Percentage>");
        pos2 = imported.find("</Percentage>");
        string l = "<Percentage>";
        pos1 += l.length();
        percentage = imported.substr(pos1, pos2 - pos1);

        pos1 = imported.find("<Duration>");
        pos2 = imported.find("</Duration>");
        string l = "<Duration>";
        pos1 += l.length();
        duration = imported.substr(pos1, pos2 - pos1);


    }else{
        //throw .....
    }
} 

Buff::~Buff(){
    delete effect;
    delete percentage;
    delete duration;
}

virtual string Buff::export() {       
    string s = "<Buff>";
    s += Consumable::export();
    s += "<Effect>" + effect + "</Effect>";
    s += "<Percentage>" + percentage + "</Percentage>";
    s += "<duration>" + duration + "</duration>";
    s += "</Buff>";
    return s;
}





