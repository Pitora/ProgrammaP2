#include<iostream>

using namespace std;

class Ammo : public Consumable {

private:

    const string attack_type;  
    const int attack_value;
    const int recoil;
    const int reload_time;
    
public:

	Ammo();

    ~Ammo();

	//virtual List<string> getInfo() {};

    //virtual int scaling() {};



};