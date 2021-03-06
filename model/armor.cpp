#include "armor.h"

Armor::Armor(){}

Armor::Armor(std::string a_t, std::string r, int d_v, int d) : armor_type(a_t), resistance(r), defense_value(d_v), durability(d) {}

Armor::Armor(int i, std::string n, std::string a_t, std::string r, int d_v, int d) : Obj(i,n), armor_type(a_t), resistance(r), defense_value(d_v), durability(d) {}

Armor::Armor(std::string imported) : Obj(imported){     //import
    if (sm::checkKW(imported,"<Armor>","</Armor>"))
    {
        armor_type = sm::substring(imported, "<ArmorType>", "</ArmorType>");
        resistance = sm::substring(imported, "<Res>", "</Res>");
        defense_value = stoi(sm::substring(imported, "<DefValue>", "</DefValue"));
        durability = stoi(sm::substring(imported, "<Durability>", "</Durability>"));
    }else throw err_import();

} 

Armor::~Armor() {
    //std::cout<<"Distrutta armatura"<<std::endl;
}

Armor* Armor::clone() const {return new Armor(*this);}


void Armor::print(std::ostream& os) const{
    Obj::print(os);
    os<<"Armor type : "<<armor_type<<std::endl;
    os<<"Resistance : "<<resistance<<std::endl;
    os<<"Defense value : "<<defense_value<<std::endl;
    os<<"Durability : "<<durability<<std::endl;
}

std::string Armor::exp() const{         //export
    std::string s = "<Armor>";
    s += Obj::exp();
    s += "<ArmorType>" + armor_type + "</ArmorType>";
    s += "<Res>" + resistance + "</Res>";
    s += "<DefValue>" + std::to_string(defense_value) + "</DefValue>";
    s += "<Durability>" + std::to_string(durability) + "</Durability>";
    s += "</Armor>";
    return s;
}

std::string Armor::getInfo() const{
    std::string s = Obj::getInfo();
    s += "Armor type : " + armor_type + "\n";
    s += "Resistance : " + resistance + "\n";
    s += "Defense value : " + std::to_string(defense_value) + "\n";
    s += "Durability : " + std::to_string(durability) + "\n";
    return s;
}

int Armor::getDefense() const {return defense_value;}

std::string Armor::getArmorType() const{return armor_type;}

std::string Armor::getArmorRes() const{return resistance;}


