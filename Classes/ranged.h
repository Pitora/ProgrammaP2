#include<iostream>
#include "ammo.h"
#include "tc.cpp"
#include "tdeep.cpp"

using namespace std;

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

	Ranged(dList<DeepPtr<Magazine>> a, int rec, int rel) : eq_ammo(a), recoil(rec), reload_time(rel);

    ~Ranged();

	//virtual List<string> getInfo() {};

    //virtual int scaling() {};

	virtual string export() {};

    virtual void import(string imported) {}; 



};
