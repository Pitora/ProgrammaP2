#include<iostream>
#include <string>

using namespace std;

class Ammo : public Consumable {

private:

    string attack_type;  
    int attack_value;  

    
public:

	Ammo(string a_t, int a_v);

    Ammo(string imported);

    ~Ammo();

	//virtual List<string> getInfo() {};

    //virtual int scaling() {};

    virtual string export();



};
