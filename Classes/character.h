#ifndef CHARACTER_H
#define CHARACTER_H

#include<iostream>
#include<string>
#include "armor.h"
#include "weapon.h"
#include "consumable.h"
#include "tc.cpp"
#include "tdeep.cpp"

class Character {

private:

    std::string name_build;
    DeepPtr<Weapon> eq_weap;
    C<DeepPtr<Armor>> eq_armor;
    C<DeepPtr<Consumable>> inventory;
    //Nomi temporanei
    int statA; 
    int statB;
    int statC;
    int statD;
    
public:

    Character();

	Character(std::string n, Weapon *wp, C<DeepPtr<Armor>> armor, C<DeepPtr<Consumable>> inv); 

    Character(std::string imported);
    ~Character();

    //metodi input/output build, se non implementati su collection.

    int scaling();

    int scalingElem();

    std::string exp();

    //void import(string imported);

};

#endif