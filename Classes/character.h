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
    int vit; 
    int str;
    int dex;
    int aim; //brutto nome
    
public:

    Character();

	Character(std::string n, DeepPtr<Weapon> wp, C<DeepPtr<Armor>> armor, C<DeepPtr<Consumable>> inv); 

    Character(std::string imported);
    ~Character();

    virtual Character* clone() const {return new Character(*this);}

    int damage() const;

    int defense() const;

    std::string exp();

    //void import(string imported);

};

#endif