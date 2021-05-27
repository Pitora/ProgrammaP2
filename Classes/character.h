#include<iostream>
#include<string.h>
#include "armor.h"
#include "weapon.h"
#include "consumable.h"
#include "tc.h"
#include "tdeep.h"


using namespace std;

class Character {

private:

    string name;
    Weapon eq_weap;
    dList<DeepPtr<Armor>> eq_armor;
    dList<DeepPtr<Consumable>> inventory;
    //Nomi temporanei
    int statA; 
    int statB;
    int statC;
    int statD;
    
public:

	Character();

    ~Character();

    //metodi input/output build, se non implementati su collection.

};