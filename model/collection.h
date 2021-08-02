#ifndef COLLECTION_H
#define COLLECTION_H

#include<iostream>
#include<string>
#include<vector>
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
    std::vector<DeepPtr<Character>> charas;
    unsigned int totalCharas;
    unsigned int nextId;
    
public:

Collection();

~Collection();

//metodi per lettura/salvataggio
void initialize();
void save() const;

//metodi per aggiungere nuovi oggetti
int getNewId();
void add(std::string n, std::string a_t, std::string r, int d_v, int d);   //Armor
void add(std::string n, int w, int c, int r, int rav, int cc, int s_str, int s_dex, int s_aim, std::string a_t, std::string a_e, int d); //Melee
void add(std::string n, int w, int c, int r, int rav, int cc, int s_str, int s_dex, int s_aim, int rec, int rel, int m); //Ranged
void add(std::string n, std::string e, int p, int d); //Buff
void add(std::string n, std::string a_v, int p);   //Healing


//Metodi usati per l'interazione con gli oggetti
C<DeepPtr<Obj>>::const_iterator getIter(int id) const;
void remove(int id);
void show(int id) const;
C<DeepPtr<Obj>> getObjPerType(std::string type, std::string type2) const;
std::string getInfoObj(int id) const;
const C<DeepPtr<Obj>> getAllObj() const;

//metodi di import/export
std::string readFile(std::string filename);
bool checkId(const int id) const;
void importObj(std::string filename);
void exportObj(int i, std::string filename);
void importChara(std::string filename);
void exportChara(int i, std::string filename);


//metodi per interagire con character
//set
void createDefaultChar();
void deleteChar(int i);
void modifyCharName(int i, std::string s);
void modifyCharWeap(int i, int id);
void modifyCharArmor(int i, int id1, int id2);
void modifyCharArmorAlt(int i, int id);
void modifyCharInv(int i, int id1, int id2);
void removeCharEq(int i , int id);
void setCharVit(int i, int x);
void setCharStr(int i, int x);
void setCharDex(int i, int x);
void setCharAim(int i ,int x);
void checkEq(int id);

void maxAtk(int i);
void maxDefense(int i);

//get
const C<std::string> getCharsName() const;
const std::string getCharName(int i) const;
const C<int> getCharStats(int i) const;
const DeepPtr<Weapon> getCharWeapon(int i) const;
const C<DeepPtr<Armor>> getCharArmor(int i) const;
const C<DeepPtr<Consumable>> getCharCons(int i) const;
int getCharAtk(int i) const;
int getCharDef(int i) const;
const DeepPtr<Character> getChar(int i) const;







};

#endif
