#include <iostream>
#include "collection.h"
#include "consumable.h"
#include "weapon.h"

using namespace std;

int main()
{

    //Consumable* h = new Consumable();

    Collection c;

    std::cout<<"Ciao"<<std::endl;

    C<DeepPtr<Obj>> esempio = c.getObjType("Consumable", "");

    std::cout<<"Filtro riuscito"<<std::endl;


    for (C<DeepPtr<Obj>>::const_iterator i = esempio.begin(); i != esempio.end(); ++i)
    {
        std::cout<<*i<<std::endl;
    }

    //C<DeepPtr<Obj>> c;

    //DeepPtr<Weapon> w;

    // c.add("Armatura del sole", "Petto", "Sanguinamento", 80, 400);

    // c.add("Armatura della luna", "Elmo", "Sanguinamento", 75, 400);
    // c.add("Armatura del crepuscolo", "Guanti", "Sanguinamento", 85, 400);
    // c.add("Armatura del Pinco", "Petto", "Gambe", 90, 400);
    // c.add("Armatura del Panco", "Petto", "Elmo", 95, 400);
    // c.add("Armatura del Solitarie", "Petto", "Guanti", 100, 400);
    // c.add("Armatura del Ciao", "Petto", "Gambe", 70, 400);
    // c.add("Armatura del non so cosa scrivere", "Petto", "Sanguinamento", 60, 400);


    // c.add("Spada del sole", 15, 20000, 12, 380, 50, 40, 40, 40, "slash", "no effect", 400);

    // c.add("Lancia del culo", 15, 20000, 12, 380, 50, 40, 40, 40, "pierce", "bleeding", 400);

    // c.add("Balestra del sole", 30, 30000, 12, 200, 20, 20, 20, 80, 4, 10, 100);

    // c.add("Droga", "Attack up", 150, 10);

    // c.add("The radiance", "HP", 50);

    // std::cout<<"AGGIUNTO TUTTO"<<std::endl;

    // c.modifyCharName("Prova");
    // c.addCharArmor(0,-1);
    // c.addCharArmor(1,-1);
    // c.addCharArmor(2,-1);
    // c.addCharArmor(3,-1);
    // c.modifyCharWeap(9);
    // c.addCharInv(12,-1); 
    // c.setCharVit(10);
    // c.setCharStr(11);
    // c.setCharDex(12);
    // c.setCharAim(13); 

    // std::cout<<"FATTE MODIFICHE A CHARACTER"<<std::endl;

    // c.exportChara("Chara.xml");

    // std::cout<<"FATTO EXPORT"<<std::endl;

    // c.modifyCharName("Prova2");
    // c.modifyCharWeap(8);
    // c.addCharArmor(4,0);
    // c.addCharInv(11,12);
    // c.removeCharEq(1);
    // c.setCharVit(14);
    // c.setCharStr(15);
    // c.setCharDex(16);
    // c.setCharAim(17); 
    // c.importChara("Chara.xml");



    // c.exportChara("Chara2.xml");

    // std::cout<<"FATTO EXPORT"<<std::endl;

    // c.show(9);
    // c.show(0); 


    // c.exportObj(0, "Armor.xml");

    // c.exportObj(1, "Weapon.xml");

    // c.exportObj(2, "Ranged.xml");

    // c.exportObj(3, "Buff.xml");

    // c.exportObj(4, "Healing.xml");

    // c.exportObj(100000, "Ciao.xml");

    //c.importObj("Armor.xml");

    //c.importObj("Weapon.xml");

    //c.importObj("Ranged.xml");

    //c.importObj("Buff.xml");

    //c.importObj("Healing.xml");

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