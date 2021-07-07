#ifndef RANGED_H
#define RANGED_H

#include<iostream>
#include <string>
#include "weapon.h"


class Ranged : public Weapon {

private:

	int recoil;   
    int reload_time;  
	int magazine;
    
public:

	Ranged(int rec, int rel, int m);

	Ranged(std::string imported);

    ~Ranged();

	virtual Ranged* clone() const {return new Ranged(*this);}

	void print(std::ostream& os);

	//virtual List<string> getInfo() {};

    //virtual int scaling() {};

	virtual std::string exp();

};

#endif