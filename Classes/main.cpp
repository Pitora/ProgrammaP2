#include <iostream>
#include "collection.h"

using namespace std;

int main()
{

    Collection c;

    c.add("Armatura del sole", "Petto", "Sanguinamento", 80, 400);

    c.exportObj(0, "Asdf.xml");

    cout<<"Hello World"<<std::endl;

    c.exportObj(0, "Asciao.xml");
    

    return 0;
}