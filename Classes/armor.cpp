#include "armor.h"

Armor::Armor(std::string a_t, unsigned int d_v, unsigned int d) : armor_type(a_t), defense_value(d_v), durability(d) {}

Armor::Armor(std::string imported) : Obj(imported){       
    if (imported.find("<Armor>") != -1 && imported.find("</Armor>") != -1)
    {
        size_t pos1 = imported.find("<ArmorType>");
        size_t pos2 = imported.find("</ArmorType>");
        std::string l = "<ArmorType>";
        pos1 += l.length();
        armor_type = imported.substr(pos1, pos2 - pos1); //Attenzione : length legge bytes di lunghezza e quindi non sempre corrispondono

        pos1 = imported.find("<DefenseValue>");
        pos2 = imported.find("</DefenseValue>");
        l = "<DefenseValue>";
        pos1 += l.length();
        defense_value = stoi(imported.substr(pos1, pos2 - pos1));

        pos1 = imported.find("<Durability>");
        pos2 = imported.find("</Durability>");
        l = "<Durability>";
        pos1 += l.length();
        durability = stoi(imported.substr(pos1, pos2 - pos1));


    }else{
        //throw .....
    }

} 

Armor::~Armor() {
    std::cout<<"Distrutta armatura"<<std::endl;
}

int Armor::damageCalculation (int attack_value) {} //Serve una formula decente (potrebbe essere necessaria l'aggiunta di qualche altro valore)

std::string Armor::exp() {     
    std::string s = "<Armor>";
    s += Obj::exp();
    s += "<ArmorType>" + armor_type + "</ArmorType>";
    s += "<DefenseValue>" + std::to_string(defense_value) + "</DefenseValue>";
    s += "<Durability>" + std::to_string(durability) + "</Durability>";
    s += "</Armor>";
    return s;
}




