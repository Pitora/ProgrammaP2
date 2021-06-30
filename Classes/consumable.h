#include<iostream>

using namespace std;

class Consumable : public Object {

private:

    string s;
    

    
public:

	Consumable(string imported) : Object(imported);

    ~Consumable();

	virtual int useObject () {} = 0;

    virtual string export() { return Object::export(); };

    virtual void import(string imported) {}; 



};