#include<iostream>

using namespace std;

class Ammo : public Consumable {

private:

    string attack_type;  
    int attack_value;  

    
public:

	Ammo(string a_t, int a_v) : attack_type(a_t), attack_value(a_v);

    ~Ammo();

	//virtual List<string> getInfo() {};

    //virtual int scaling() {};

    virtual string export() {};

    virtual void import(string imported) {}; 



};
