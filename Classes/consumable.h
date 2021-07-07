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

	Consumable(std::string imported);

    ~Consumable();

    virtual Consumable* clone() const {return new Consumable(*this);}

    void print(std::ostream& os) { Obj::print(os);}

	virtual int useObject ();

    virtual std::string exp();
 


};

#endif