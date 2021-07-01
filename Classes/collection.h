#include<iostream>
#include<string>
#include "object.h"
#include "character.h"
#include "tc.cpp"
#include "tdeep.cpp"


class Collection {

private:

    dList<DeepPtr<Obj>> list;
    Character chara;      
    
public:



void initialize();

void update();

void add();   //forse necessario per ogni classe

void remove(int i);


//getinfo



void importObj(std::string s);

void exportObj(int i, std::string s);

void importChara();

void exportChara();



};