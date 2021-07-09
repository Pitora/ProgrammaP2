#ifndef CONSUMABLE_H
#define CONSUMABLE_H

#include<iostream>
#include <string>
#include "object.h"

class Consumable : public Obj {

private:

    //string s; 
    
public:

    Consumable();

    Consumable(int i, std::string n);

	Consumable(std::string imported);

    ~Consumable();

    virtual Consumable* clone() const {return new Consumable(*this);}

    void print(std::ostream& os) const { Obj::print(os);}

	virtual int useObject ();

    virtual std::string exp() const;
 


};

#endif