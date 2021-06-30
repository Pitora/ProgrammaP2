#include <iostream>
#include <string>
#include "armor.h"

using namespace std;

Armor::Armor(string a_t, unsigned int d_v, unsigned int d) : armor_type(a_t), defense_value(d_v), durability(d) {}

Armor::Armor(string imported) : Object(imported){       
    if (imported.find("<Armor>") != -1 && imported.find("</Armor>") != -1)
    {
        size_t pos1 = imported.find("<ArmorType>");
        size_t pos2 = imported.find("</ArmorType>");
        string l = "<ArmorType>";
        pos1 += l.length();
        armor_type = imported.substr(pos1, pos2 - pos1); //Attenzione : length legge bytes di lunghezza e quindi non sempre corrispondono

        pos1 = imported.find("<DefenseValue>");
        pos2 = imported.find("</DefenseValue>");
        string l = "<DefenseValue>";
        pos1 += l.length();
        defense_value = imported.substr(pos1, pos2 - pos1);

        pos1 = imported.find("<Durability>");
        pos2 = imported.find("</Durability>");
        string l = "<Durability>";
        pos1 += l.length();
        durability = imported.substr(pos1, pos2 - pos1);


    }else{
        //throw .....
    }

} 

~Armor() {                  
    delete armor_type;
    delete defense_value;
    delete durability;
};

int Armor::damageCalculation (int attack_value) {} //Serve una formula decente (potrebbe essere necessaria l'aggiunta di qualche altro valore)

virtual string Armor::export() {     
    string s = "<Armor>";
    s += Object::export();
    s += "<ArmorType>" + armor_type + "</ArmorType>";
    s += "<DefenseValue>" + defense_value + "</DefenseValue>";
    s += "<Durability>" + durability + "</Durability>";
    s += "</Armor>";
    return s;
}




