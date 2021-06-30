#include<iostream>

using namespace std;

class Healing : public Consumable {

private:

    string affected_value;  
    unsigned int potency;
    
public:

	Healing(string a_v, unsigned int p);

    Healing(string imported);

    ~Healing();

    virtual string export();

};