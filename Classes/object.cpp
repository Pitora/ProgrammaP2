#include <iostream>
#include <string>
#include "object.h"

using namespace std;

Object::Object(int i, int n) : id(i), name(n);

Object::Object(string imported){
    size_t pos1 = imported.find("<Id>");
    size_t pos2 = imported.find("</Id>");
    string s = "<Id>";
    pos1 += s.length();
    id = Int(str.substr(pos1,pos2-pos1));

    pos1 = imported.find("<Name>");
    pos2 = imported.find("</Name>");
    s = "<Name>";
    pos1 += s.length();
    name = str.substr(pos1, pos2-pos1);
}

virtual Object::~Object() {
    delete id;
    delete name;
}

int getId() {return id;}

string getName() {return name;}


virtual string Object::export() {       //Esempio di export?
    string s = "<Object>";
    s += "<Id>" + id + "</Id>";
    s += "<Name>" + name + "</Name>";
    s += "</Object>";
    return s;
}




