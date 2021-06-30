#include<iostream>
#include<string.h>
#include "armor.h"
#include "weapon.h"
#include "consumable.h"
#include "tc.cpp"
#include "tdeep.cpp"


using namespace std;

class Character {

private:

    string name_build;
    DeepPtr<Weapon> eq_weap;
    dList<DeepPtr<Armor>> eq_armor;
    dList<DeepPtr<Consumable>> inventory;
    //Nomi temporanei
    int statA; 
    int statB;
    int statC;
    int statD;
    
public:

	Character(string n, Weapon *wp, dList<DeepPtr<Armor>> armor, dList<DeepPtr<Consumable>> inv); 
    ~Character();

    //metodi input/output build, se non implementati su collection.

    int scaling();

    int scalingElem();

    string export();

    void import(string imported);

    

};