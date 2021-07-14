#ifndef OBJECT_H
#define OBJECT_H

#include<iostream>
#include <string>
#include "stringm.h"
#include "exceptions.h"


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

    bool operator== (const Obj& x) const;

    friend std::ostream& operator<<(std::ostream& s, const Obj& base);

    virtual std::string exp() const;

    virtual void print(std::ostream& os) const;

    virtual std::string getInfo() const;

    int getId() const;

    std::string getName() const;


};


#endif




