#ifndef MELEE_H
#define MELEE_H

#include<iostream>
#include <string>
#include "weapon.h"
#include "stringm.h"
#include "exceptions.h"


class Melee : public Weapon {

private:

    std::string attack_type;  
    std::string added_effect;
    unsigned int durability;
    

    
public:

	Melee(std::string a_t, std::string a_e, unsigned int d);

    Melee(int i, std::string n, int w, int c, int r, int rav, int cc, int s_str, int s_dex, int s_aim, std::string a_t, std::string a_e, unsigned int d);

    Melee(std::string imported);

    virtual ~Melee();

    virtual Melee* clone() const;

    void print(std::ostream& os) const;

    virtual std::string exp() const;

    virtual std::string getInfo() const;

};

#endif
