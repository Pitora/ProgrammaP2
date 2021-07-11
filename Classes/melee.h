#ifndef MELEE_H
#define MELEE_H

#include<iostream>
#include <string>
#include "weapon.h"
#include "exceptions.cpp"


class Melee : public Weapon {

private:

    std::string attack_type;  
    std::string added_effect;
    unsigned int durability;
    

    
public:

	Melee(std::string a_t, std::string a_e, unsigned int d);

    Melee(int i, std::string n, int w, int c, int r, int rav, int cc, int s_str, int s_dex, int s_aim, std::string a_t, std::string a_e, unsigned int d);

    Melee(std::string imported);

    ~Melee();

    virtual Melee* clone() const {return new Melee(*this);}

    void print(std::ostream& os) const;

	//virtual List<string> getInfo() {};

    //virtual int scaling() {};

    virtual std::string exp() const;

};

#endif
