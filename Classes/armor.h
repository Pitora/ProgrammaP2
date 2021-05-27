#include<iostream>

using namespace std;

class Armor : public Object {

private:

    const string armor_type;  
    const unsigned int defense_value;
    const unsigned int durability;
    
public:

	Armor();

    ~Armor();

    int damageCalculation (int attack_value) {};

};
