#ifndef RANGED_H
#define RANGED_H

#include<iostream>
#include <string>
#include "ammo.h"
#include "tc.cpp"
#include "tdeep.cpp"
#include "weapon.h"

struct Magazine {
	DeepPtr<Ammo> type;
	int count;
};

class Ranged : public Weapon {

private:

    dList<DeepPtr<Magazine>> eq_ammo;
	int recoil;   
    int reload_time;  
    
public:

	Ranged(dList<DeepPtr<Magazine>> a, int rec, int rel);

	Ranged(std::string imported);

    ~Ranged();

	//virtual List<string> getInfo() {};

    //virtual int scaling() {};

	virtual std::string exp();

};

#endif