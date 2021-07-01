#ifndef BUFF_H
#define BUFF_H

#include<iostream>
#include <string>
#include "consumable.h"


class Buff : public Consumable {

private:

    std::string effect;  
    unsigned int percentage;
    unsigned int duration;
    
public:

	Buff(std::string e, unsigned int p, unsigned int d);

    Buff(std::string imported);

    ~Buff();

    virtual std::string exp();


};

#endif