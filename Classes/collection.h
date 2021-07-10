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

~Collection();

void save();

void add(std::string n, std::string a_t, std::string r, int d_v, int d);   //Armor

void add(std::string n, int w, int c, int r, int rav, int cc, int s_str, int s_dex, int s_aim, std::string a_t, std::string a_e, int d); //Melee

void add(std::string n, int w, int c, int r, int rav, int cc, int s_str, int s_dex, int s_aim, int rec, int rel, int m); //Ranged

void add(std::string n, std::string e, int p, int d); //Buff

void add(std::string n, std::string a_v, int p);   //Healing



bool remove(int i);


//getinfo

std::string readFile(std::string filename);

bool checkId(const int id) const;

bool importObj(std::string filename);

void exportObj(int i, std::string filename);

void importChara(std::string filename);

void exportChara(std::string filename);

void show(int id);

int generateId();

void modifyCharName(std::string s);

void modifyCharEq(int id1, int id2);

C<DeepPtr<Obj>>::const_iterator getIter(int id) const;




};