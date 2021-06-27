#include<iostream>

using namespace std;

class Healing : public Consumable {

private:

    string affected_value;  
    unsigned int potency;
    
public:

	Healing(string a_v, unsigned int p) : affected_value(a_v), potency(p);

    ~Healing();

    virtual string export() {};

    virtual void import(string imported) {}; 

};