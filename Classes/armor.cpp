#include "armor.h"

Armor::Armor(std::string a_t, unsigned int d_v, unsigned int d) : armor_type(a_t), defense_value(d_v), durability(d) {}

Armor::Armor(std::string imported) : Obj(imported){       
    if (imported.find("<Armor>") != -1 && imported.find("</Armor>") != -1)
    {
        armor_type = substring(imported, "<ArmorType>", "</ArmorType>"); //Attenzione : length legge bytes di lunghezza e quindi non sempre corrispondono

        defense_value = stoi(substring(imported, "<DefValue>", "</DefValue"));

        durability = stoi(substring(imported, "<Durability>", "</Durability>"));

    }else{
        //throw .....
    }

} 

Armor::~Armor() {
    std::cout<<"Distrutta armatura"<<std::endl;
}

void Armor::print(std::ostream& os){
    Obj::print(os);
    os<<"Armor type : "<<armor_type<<std::endl;
    os<<"Defense value : "<<defense_value<<std::endl;
    os<<"Durability : "<<durability<<std::endl;
}

int Armor::damageCalculation (int attack_value) {} //Serve una formula decente (potrebbe essere necessaria l'aggiunta di qualche altro valore)

std::string Armor::exp() {     
    std::string s = "<Armor>";
    s += Obj::exp();
    s += "<ArmorType>" + armor_type + "</ArmorType>";
    s += "<DefValue>" + std::to_string(defense_value) + "</DefValue>";
    s += "<Durability>" + std::to_string(durability) + "</Durability>";
    s += "</Armor>";
    return s;
}



