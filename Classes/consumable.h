#include<iostream>

using namespace std;

class Consumable : public Object {

private:

    string s;
    

    
public:

	Consumable();

    ~Consumable();

	virtual int useObject () {} = 0;

    virtual string export() {};

    virtual void import(string imported) {}; 



};