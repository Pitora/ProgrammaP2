#include<iostream>

using namespace std;

class Consumable : public Object {

private:

    const string attack_type;  
    const unsigned int hardness;
    const unsigned int precision;
    

    
public:

	Consumable();

    ~Consumable();

	virtual int useObject () {} = 0;



};