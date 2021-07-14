#ifndef HEALING_H
#define HEALING_H

#include<iostream>
#include <string>
#include "consumable.h"
#include "stringm.h"
#include "exceptions.h"


class Healing : public Consumable {

private:

    std::string affected_value;  
    unsigned int potency;
    
public:

	Healing(std::string a_v, unsigned int p);

    Healing(int i, std::string n, std::string a_v, unsigned int p);

    Healing(std::string imported);

    virtual ~Healing();

    virtual Healing* clone() const;

    virtual void print(std::ostream& os) const;

    virtual std::string exp() const;

    virtual std::string getInfo() const;

};

#endif
