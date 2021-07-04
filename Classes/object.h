#ifndef OBJECT_H
#define OBJECT_H

#include<iostream>
#include <string>

class Obj {

private:

    unsigned int id;
    std::string name;   
    
public:

    Obj();

	Obj(int i, std::string n);

    Obj(std::string imported);

    virtual ~Obj() = 0;

    virtual Obj* clone() const = 0;

	//virtual List<string> getInfo() {} = 0;     quasi sicuro che non si possono utilizzare

    int getId() {return id;}

    std::string getName() {return name;}

    bool operator== (const Obj& x) const {return id == x.id;}

    virtual std::string exp();

    static std::string substring (std::string s, std::string w1, std::string w2);

};

#endif




