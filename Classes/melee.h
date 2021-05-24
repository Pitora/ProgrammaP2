#include<iostream>

using namespace std;

class Melee : public Weapon {

private:

    const string attack_type;  
    const unsigned int hardness;
    const unsigned int precision;

    
public:

	Melee();

    ~Melee();

	//virtual List<string> getInfo() {};

    //virtual int scaling() {};



};