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

	Weapon(int w, int c, int r, int rav, int eav, int cc);

    Weapon(string imported);

    ~Weapon();

	//virtual List<string> getInfo() {};

    virtual string export();



};