#ifndef BUFF_H
#define BUFF_H

#include<iostream>
#include <string>
#include "consumable.h"
#include "stringm.h"
#include "exceptions.h"

class Buff : public Consumable {

private:

    std::string effect;  
    unsigned int percentage;
    unsigned int duration;
    
public:

	Buff(std::string e, unsigned int p, unsigned int d);

    Buff(int i, std::string n, std::string e, unsigned int p, unsigned int d);

    Buff(std::string imported);

    virtual ~Buff();

    virtual Buff* clone() const;

    virtual void print(std::ostream& os) const;

    virtual std::string exp() const;

    virtual std::string getInfo() const;

};

#endif
