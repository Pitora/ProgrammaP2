#include<iostream>

using namespace std;

class Buff : public Consumable {

private:

    const string effect;  
    const unsigned int percentage;
    const unsigned int duration;
    
public:

	Buff();

    ~Buff();

};