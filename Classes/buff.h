#include<iostream>

using namespace std;

class Buff : public Consumable {

private:

    string effect;  
    unsigned int percentage;
    unsigned int duration;
    
public:

	Buff(string e, unsigned int p, unsigned int d);

    Buff(string imported);

    ~Buff();

    virtual string export() ;


};