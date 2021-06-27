#include<iostream>

using namespace std;

class Weapon : public Object {

private:

    unsigned int weight;  
    unsigned int cost;
    unsigned int rarity;
    unsigned int raw_attack_value;
    unsigned int elem_attack_value;
    unsigned int critical_chance;
    //altre variabili per lo scaling

    
public:

	Weapon(int w, int c, int r, int rav, int eav, int cc) : weight(w), cost(c), rarity(r), raw_attack_value(rav), elem_attack_value(eav), critical_chance(cc);

    ~Weapon();

	//virtual List<string> getInfo() {};

    virtual string export() {};

    virtual void import(string imported) {}; 


};