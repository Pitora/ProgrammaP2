#include<iostream>

using namespace std;

class Melee : public Weapon {

private:

    string attack_type;  
    unsigned int durability;
    unsigned int precision;

    
public:

	Melee(string a_t, unsigned int d, unsigned int p);

    Melee(string imported);

    ~Melee();

	//virtual List<string> getInfo() {};

    //virtual int scaling() {};

    virtual string export() {};

    



};
