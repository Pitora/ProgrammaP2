#include "consumable.h"

Consumable::Consumable() {}

Consumable::Consumable(int i, std::string n) : Obj(i,n) {}

Consumable::Consumable(std::string imported) : Obj(imported) {}

Consumable::~Consumable() {
    std::cout<<"Consumabile cancellato"<<std::endl;
}


std::string Consumable::exp() const { return Obj::exp(); }

std::string Consumable::getInfo() const {return Obj::getInfo(); }
