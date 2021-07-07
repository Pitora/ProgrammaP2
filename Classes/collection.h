#include<iostream>
#include<string>
#include<fstream>
#include "object.h"
#include "melee.h"
#include "ranged.h"
#include "buff.h"
#include "healing.h"
#include "character.h"
#include "tc.cpp"
#include "tdeep.cpp"


class Collection {

private:

    C<DeepPtr<Obj>> list;
    Character chara;      
    
public:

Collection();

void initialize();

void save();

void update();

void add();   //forse necessario per ogni classe

void remove(int i);


//getinfo

std::string readFile(std::string filename);

bool checkCopy(DeepPtr<Obj>& o) const;

bool importObj(std::string filename);

void exportObj(int i, std::string filename);

void importChara();

void exportChara();




};