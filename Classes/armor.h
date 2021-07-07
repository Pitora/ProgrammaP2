#ifndef ARMOR_H
#define ARMOR_H

#include<iostream>
#include<string>
#include "object.h"

class Armor : public Obj {

private:

    std::string armor_type;  
    unsigned int defense_value;
    unsigned int durability;
    
public:

	Armor(std::string a_t, unsigned int d_v, unsigned int d);

    Armor(std::string imported);

    ~Armor();

    virtual Armor* clone() const {return new Armor(*this);}

    virtual void print(std::ostream& os);

    int damageCalculation (int attack_value);

    virtual std::string exp();

    int getDefense() const;

};

#endif
