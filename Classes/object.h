#include<iostream>

using namespace std;

class Object {

private:

    unsigned int id;
    string name;   
    
public:

	Object(int i, int n);

    Object(string imported);

    virtual ~Object() = 0;

    

	//virtual List<string> getInfo() {} = 0;     quasi sicuro che non si possono utilizzare

    int getId();

    string getName();

    virtual string export();

};




