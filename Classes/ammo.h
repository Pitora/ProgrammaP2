#include<iostream>

using namespace std;

class Ammo : public Consumable {

private:

    const string attack_type;  
    const int attack_value;  
    const int recoil;   //<--- lo metterei nelle armi non nelle munzioni
    const int reload_time;  // stessa roba del recoil
    
public:

	Ammo();

    ~Ammo();

	//virtual List<string> getInfo() {};

    //virtual int scaling() {};



};
