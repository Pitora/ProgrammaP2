#include<iostream>
#include "ammo.h"
#include "tc.h"
#include "tdeep.h"

using namespace std;

struct Packet {
	Ammo type;
	int count;
};

class Ranged : public Weapon {

private:

    dList<DeepPtr<Packet>> eq_ammo;
    
public:

	Ranged();

    ~Ranged();

	//virtual List<string> getInfo() {};

    //virtual int scaling() {};



};