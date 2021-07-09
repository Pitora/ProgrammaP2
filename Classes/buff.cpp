#include "buff.h"


Buff::Buff(std::string e, unsigned int p, unsigned int d) : effect(e), percentage(p), duration(d) {}

Buff::Buff(int i, std::string n, std::string e, unsigned int p, unsigned int d) : Consumable(i,n), effect(e), percentage(p), duration(d) {}

Buff::Buff(std::string imported) : Consumable(imported){       
    if (imported.find("<Buff>") != -1 && imported.find("</Buff>") != -1)
    {
        effect = substring(imported, "<Effect>", "</Effect>"); //Attenzione : length legge bytes di lunghezza e quindi non sempre corrispondono

        percentage = stoi(substring(imported,"<Percentage>", "</Percentage>"));

        duration = stoi(substring(imported, "<Duration>", "</Duration>"));

    }else{
        //throw .....
    }
} 

Buff::~Buff(){
    std::cout<<"Cancellato un buff"<<std::endl;
}

void Buff::print(std::ostream& os){
    Consumable::print(os);
    os<<"Effect : "<<effect<<std::endl;
    os<<"Percentage : "<<percentage<<std::endl;
    os<<"Duration : "<<duration<<std::endl;
}

std::string Buff::exp() const{       
    std::string s = "<Buff>";
    s += Consumable::exp();
    s += "<Effect>" + effect + "</Effect>";
    s += "<Percentage>" + std::to_string(percentage) + "</Percentage>";
    s += "<Duration>" + std::to_string(duration) + "</Duration>";
    s += "</Buff>";
    return s;
}





