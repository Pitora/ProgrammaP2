#include<iostream>
#include "object.h"
#include "character.h"
#include "tc.cpp"
#include "tdeep.cpp"

using namespace std;

class Collection {

private:

    dList<DeepPtr<Object>> list;
    Character chara;      
    
public:



static void initialize();

void update();

void add();   //forse necessario per ogni classe

void remove(int i);


//getinfo



static void importObj(string s);

static void exportObj(int i, string s);

static void importChara();

static void exportChara();



};