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
    dList<DeepPtr<Armor>> eq_armor;
    dList<DeepPtr<Consumable>> inventory;
    //Nomi temporanei
    int statA; 
    int statB;
    int statC;
    int statD;
    
public:

	Character(std::string n, Weapon *wp, dList<DeepPtr<Armor>> armor, dList<DeepPtr<Consumable>> inv); 
    ~Character();

    //metodi input/output build, se non implementati su collection.

    int scaling();

    int scalingElem();

    std::string exp();

    //void import(string imported);

    

};