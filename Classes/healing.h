#include<iostream>

using namespace std;

class Healing : public Consumable {

private:

    const string affected_value;  
    const unsigned int potency;
    
public:

	Healing();

    ~Healing();


};