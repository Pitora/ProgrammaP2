#include <iostream>
#include "collection.h"
#include "consumable.h"
#include "weapon.h"

using namespace std;

int main()
{

    //Consumable* h = new Consumable();

    Collection c;

    //C<DeepPtr<Obj>> c;

    //DeepPtr<Weapon> w;

    // c.add("Armatura del sole", "Petto", "Sanguinamento", 80, 400);

    // c.add("Spada del sole", 15, 20000, 12, 380, 50, 40, 40, 40, "slash", "no effect", 400);

    // c.add("Balestra del sole", 30, 30000, 12, 200, 20, 20, 20, 80, 4, 10, 100);

    // c.add("Droga", "Attack up", 150, 10);

    // c.add("The radiance", "HP", 50);

    // c.exportObj(0, "Armor.xml");

    // c.exportObj(1, "Weapon.xml");

    // c.exportObj(2, "Ranged.xml");

    // c.exportObj(3, "Buff.xml");

    // c.exportObj(4, "Healing.xml");

    // c.exportObj(100000, "Ciao.xml");

    c.importObj("Armor.xml");

    c.importObj("Weapon.xml");

    c.importObj("Ranged.xml");

    c.importObj("Buff.xml");

    c.importObj("Healing.xml");

    //cout<<"Hello World"<<std::endl;

    //c.exportObj(0, "Asciao.xml");

    // c.importObj("Asciao.xml");

    // c.importObj("NonEsisto.xml");

    // c.importObj("Healing.xml");

    // c.show(100000);

    // c.show(10000);

    // c.remove(100000);

    // c.remove(2);

    //c.primo();

    return 0;
}