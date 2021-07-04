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
    unsigned int elem_attack_value;
    unsigned int critical_chance;
    //altre variabili per lo scaling

    
public:

    Weapon();

	Weapon(int w, int c, int r, int rav, int eav, int cc);

    Weapon(std::string imported);

    ~Weapon();

    virtual Weapon* clone() const {return new Weapon(*this);}

	//virtual List<string> getInfo() {};

    virtual std::string exp();

};

#endif