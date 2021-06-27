#include<iostream>

using namespace std;

class Buff : public Consumable {

private:

    string effect;  
    unsigned int percentage;
    unsigned int duration;
    
public:

	Buff(string e, unsigned int p, unsigned int d) : effect(e);

    ~Buff();

    virtual string export() {};

    virtual void import(string imported) {}; 


};