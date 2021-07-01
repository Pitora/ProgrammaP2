#include<iostream>
#include <string>
#include "consumable.h"



class Ammo : public Consumable {

private:

    std::string attack_type;  
    int attack_value;  

    
public:

	Ammo(std::string a_t, int a_v);

    Ammo(std::string imported);

    ~Ammo();

	//virtual List<string> getInfo() {};

    //virtual int scaling() {};

    virtual std::string exp();



};
