#include <iostream>
#include <string>
#include "object.h"

using namespace std;

virtual string Object::export() {       //Esempio di export?
    string s = "<Object>";
    s += "<Id>" + id + "</Id>";
    s += "<Name>" + name + "</Name>";
    s += "</Object>";
    return s;
}

virtual void Object::import(string imported){       //esempio di import?
    size_t pos1 = imported.find("<Id>");
    size_t pos2 = imported.find("</Id>");
    id = Int(str.substr(pos1+5,pos2-pos1));

    pos1 = imported.find("<Name>");
    pos2 = imported.find("</Name>");
    name = str.substr(pos1+7, pos2-pos1);
} 


