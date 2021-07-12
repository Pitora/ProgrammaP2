#ifndef BUFF_H
#define BUFF_H

#include<iostream>
#include <string>
#include "consumable.h"
#include "exceptions.cpp"


class Buff : public Consumable {

private:

    std::string effect;  
    unsigned int percentage;
    unsigned int duration;
    
public:

	Buff(std::string e, unsigned int p, unsigned int d);

    Buff(int i, std::string n, std::string e, unsigned int p, unsigned int d);

    Buff(std::string imported);

    ~Buff();

    virtual Buff* clone() const {return new Buff(*this);}

    virtual void print(std::ostream& os) const;

    virtual std::string exp() const;

    virtual std::string getInfo() const;

};

#endif
