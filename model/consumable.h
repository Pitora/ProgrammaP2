#ifndef CONSUMABLE_H
#define CONSUMABLE_H

#include<iostream>
#include <string>
#include "object.h"
#include "stringm.h"
#include "exceptions.h"


class Consumable : public Obj {

private:

    
public:

    Consumable();

    Consumable(int i, std::string n);

	Consumable(std::string imported);

    virtual ~Consumable();

    virtual Consumable* clone() const;

    void print(std::ostream& os) const;

    virtual std::string exp() const;

    virtual std::string getInfo() const;
 


};

#endif
