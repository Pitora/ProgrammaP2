#ifndef COLLECTION_H
#define COLLECTION_H

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
#include "stringm.h"
#include "exceptions.h"

class Collection {

private:

    C<DeepPtr<Obj>> list;
    Character chara;      
    
public:

Collection();

~Collection();

void initialize();

void save();

void add(std::string n, std::string a_t, std::string r, int d_v, int d);   //Armor

void add(std::string n, int w, int c, int r, int rav, int cc, int s_str, int s_dex, int s_aim, std::string a_t, std::string a_e, int d); //Melee

void add(std::string n, int w, int c, int r, int rav, int cc, int s_str, int s_dex, int s_aim, int rec, int rel, int m); //Ranged

void add(std::string n, std::string e, int p, int d); //Buff

void add(std::string n, std::string a_v, int p);   //Healing



bool remove(int id);

void checkEq(int id);


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
void modifyCharWeap(int id);
void modifyCharArmor(int id1, int id2);
void modifyCharInv(int id1, int id2);
void removeCharEq(int id);
void setCharVit(int x);
void setCharStr(int x);
void setCharDex(int x);
void setCharAim(int x);
const DeepPtr<Character> getChar() const;

C<DeepPtr<Obj>>::const_iterator getIter(int id) const;
C<DeepPtr<Obj>> getObjType(std::string type, std::string type2) const;
const C<DeepPtr<Obj>> getAllObj() const;
std::string getInfoObj(int id) const;


};

#endif
