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

    int damageCalculation (int attack_value);

    virtual std::string exp();

};
