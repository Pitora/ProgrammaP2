#include<iostream>

using namespace std;

class Object {

private:

    unsigned int id;
    string name;   
    
public:

	Object(int i, int n) : id(i), name(n);

    virtual ~Object() {} = 0;

	//virtual List<string> getInfo() {} = 0;     quasi sicuro che non si possono utilizzare

    int getId() {return id;}

    string getName() {return name;}

    virtual string export() {};

    virtual void import(string imported) {}; 

};




