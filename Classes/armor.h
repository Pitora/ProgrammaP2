#ifndef ARMOR_H
#define ARMOR_H

#include<iostream>
#include<string>
#include "object.h"

class Armor : public Obj {

private:

    std::string armor_type;  
    std::string resistance;
    unsigned int defense_value;
    unsigned int durability;
    
public:

	Armor(std::string a_t, std::string r, int d_v, int d);

    Armor(int i, std::string n, std::string a_t, std::string r, int d_v, int d);

    Armor(std::string imported);

    ~Armor();

    virtual Armor* clone() const {return new Armor(*this);}

    virtual void print(std::ostream& os) const;

    int damageCalculation (int attack_value);

    virtual std::string exp() const;

    int getDefense() const;
    std::string getArmorType() const;

};

#endif
