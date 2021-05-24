#include<iostream>

using namespace std;

class Object {

private:

    const unsigned int id;
    const string name;   
    
public:

	Object();

    ~Object();

	virtual List<string> getInfo() {} = 0;

    int getId() {return id;}

    string getName() {return nome;}

};




