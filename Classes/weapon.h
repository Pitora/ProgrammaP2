#ifndef WEAPON_H
#define WEAPON_H

#include<iostream>
#include <string>
#include "object.h"


class Weapon : public Obj{

private:

    unsigned int weight;  
    unsigned int cost;
    unsigned int rarity;
    unsigned int raw_attack_value;
    //unsigned int elem_attack_value;
    unsigned int critical_chance;
    unsigned int scaling_str;
    unsigned int scaling_dex;
    unsigned int scaling_aim;

    
public:

    Weapon();

	Weapon(int w, int c, int r, int rav, int cc, int s_str, int s_dex, int s_aim);

    Weapon(int i, std::string n, int w, int c, int r, int rav, int cc, int s_str, int s_dex, int s_aim);

    Weapon(std::string imported);

    ~Weapon();

    virtual Weapon* clone() const {return new Weapon(*this);}

    virtual void print(std::ostream& os);

	//virtual List<string> getInfo() {};

    virtual std::string exp() const;

    int getAttack() const;
    int getScalingStr() const;
    int getScalingDex() const;
    int getScalingAim() const;

};

#endif