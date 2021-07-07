#ifndef MELEE_H
#define MELEE_H

#include<iostream>
#include <string>
#include "weapon.h"


class Melee : public Weapon {

private:

    std::string attack_type;  
    unsigned int durability;

    
public:

	Melee(std::string a_t, unsigned int d, unsigned int p);

    Melee(std::string imported);

    ~Melee();

    virtual Melee* clone() const {return new Melee(*this);}

    void print(std::ostream& os);

	//virtual List<string> getInfo() {};

    //virtual int scaling() {};

    virtual std::string exp();

};

#endif
