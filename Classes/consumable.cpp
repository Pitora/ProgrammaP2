#include "consumable.h"

Consumable::Consumable() {}

Consumable::Consumable(int i, std::string n) : Obj(i,n) {}

Consumable::Consumable(std::string imported) : Obj(imported) {}

Consumable::~Consumable() {
    std::cout<<"Consumabile cancellato"<<std::endl;
}

int Consumable::useObject() {}

std::string Consumable::exp() { return Obj::exp(); }