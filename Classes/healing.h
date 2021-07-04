#ifndef HEALING_H
#define HEALING_H

#include<iostream>
#include <string>
#include "consumable.h"

class Healing : public Consumable {

private:

    std::string affected_value;  
    unsigned int potency;
    
public:

	Healing(std::string a_v, unsigned int p);

    Healing(std::string imported);

    ~Healing();

    virtual Healing* clone() const {return new Healing(*this);}

    virtual std::string exp();

};

#endif