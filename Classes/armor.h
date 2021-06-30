#include<iostream>

using namespace std;

class Armor : public Object {

private:

    string armor_type;  
    unsigned int defense_value;
    unsigned int durability;
    
public:

	Armor(string a_t, unsigned int d_v, unsigned int d);

    Armor(string imported);

    ~Armor();

    int damageCalculation (int attack_value);

    virtual string export();

};
