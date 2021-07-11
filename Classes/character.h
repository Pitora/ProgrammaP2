#ifndef CHARACTER_H
#define CHARACTER_H

#include<iostream>
#include<string>
#include "armor.h"
#include "weapon.h"
#include "melee.h"
#include "ranged.h"
#include "consumable.h"
#include "healing.h"
#include "buff.h"
#include "tc.cpp"
#include "tdeep.cpp"

class Character {

private:

    std::string name_build;
    DeepPtr<Weapon> eq_weap;
    C<DeepPtr<Armor>> eq_armor;
    C<DeepPtr<Consumable>> inventory;
    int vit; 
    int str;
    int dex;
    int aim; 
    
public:

    Character();

	Character(std::string n, DeepPtr<Weapon> wp, C<DeepPtr<Armor>> armor, C<DeepPtr<Consumable>> inv, int v, int s, int d, int a); 

    Character(std::string imported);

    ~Character();

    Character(const Character& x);

    virtual Character* clone() const {return new Character(*this);}

    std::string getName() const;

    DeepPtr<Weapon> getEqWeap() const;

    C<DeepPtr<Armor>> getEqArmor() const;

    C<DeepPtr<Consumable>> getInv() const;

    C<int> getStats() const;

    void setName(std::string s);
    void setWeap(const DeepPtr<Obj>& w);
    void disequip(const DeepPtr<Obj>& r);
    void addArmor(const DeepPtr<Obj>& a);
    void addConsum(const DeepPtr<Obj>& c);
    void setVit(int x);
    void setStr(int x);
    void setDex(int x);
    void setAim(int x);

    int damage() const;

    int defense() const;

    std::string exp() const;

    //void import(string imported);

};

#endif