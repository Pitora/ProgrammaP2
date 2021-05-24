#include<iostream>

using namespace std;

class Weapon : public Object {

private:

    const unsigned int weight;  
    const unsigned int cost;
    const unsigned int rarity;
    const unsigned int raw_attack_value;
    const unsigned int elem_attack_value;
    const unsigned int critical_chance;
    //altre variabili per lo scaling

    
public:

	Weapon();

    ~Weapon();

	virtual List<string> getInfo() {};

    int scaling() {};



};