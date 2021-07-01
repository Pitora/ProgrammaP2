#include "buff.h"


Buff::Buff(std::string e, unsigned int p, unsigned int d) : effect(e), percentage(p), duration(d) {}

Buff::Buff(std::string imported) : Consumable(imported){       
    if (imported.find("<Buff>") != -1 && imported.find("</Buff>") != -1)
    {
        size_t pos1 = imported.find("<Effect>");
        size_t pos2 = imported.find("</Effect>");
        std::string l = "<Effect>";
        pos1 += l.length();
        effect = imported.substr(pos1, pos2 - pos1); //Attenzione : length legge bytes di lunghezza e quindi non sempre corrispondono

        pos1 = imported.find("<Percentage>");
        pos2 = imported.find("</Percentage>");
        l = "<Percentage>";
        pos1 += l.length();
        percentage = stoi(imported.substr(pos1, pos2 - pos1));

        pos1 = imported.find("<Duration>");
        pos2 = imported.find("</Duration>");
        l = "<Duration>";
        pos1 += l.length();
        duration = stoi(imported.substr(pos1, pos2 - pos1));


    }else{
        //throw .....
    }
} 

Buff::~Buff(){
    std::cout<<"Cancellato un buff"<<std::endl;
}

std::string Buff::exp() {       
    std::string s = "<Buff>";
    s += Consumable::exp();
    s += "<Effect>" + effect + "</Effect>";
    s += "<Percentage>" + std::to_string(percentage) + "</Percentage>";
    s += "<duration>" + std::to_string(duration) + "</duration>";
    s += "</Buff>";
    return s;
}





