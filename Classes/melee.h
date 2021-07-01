#ifndef MELEE_H
#define MELEE_H

#include<iostream>
#include <string>
#include "weapon.h"


class Melee : public Weapon {

private:

    std::string attack_type;  
    unsigned int durability;
    unsigned int precision;

    
public:

	Melee(std::string a_t, unsigned int d, unsigned int p);

    Melee(std::string imported);

    ~Melee();

	//virtual List<string> getInfo() {};

    //virtual int scaling() {};

    virtual std::string exp();

};

#endif
