#include <iostream>
#include <string>
#include "character.h"

using namespace std;

Character(string n, Weapon *wp, dList<DeepPtr<Armor>> armor, dList<DeepPtr<Consumable>> inv) : name_build(n),eq_weap(wp),eq_armor(armor),inventory(inv)){}

~Character(){
    delete name_build;
    delete eq_weap;
    for (auto a : armor) delete eq_armor;
    for (auto i : inventory) delete inventory;
}


int Character::scaling(){
    if (eq_weap != null)
    {
        return 1; // Calcolo 
    }else{
        //return calcolo 2
    }
}

int Character::scalingElem(){
//Stessa cosa di scaling
}

string Character::export() {       
    
}

void Character::import(string imported){       

} 