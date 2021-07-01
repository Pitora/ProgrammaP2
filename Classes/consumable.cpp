#include "consumable.h"

Consumable::Consumable() {}

Consumable::Consumable(std::string imported) : Obj(imported) {}

Consumable::~Consumable() {
    std::cout<<"Consumabile cancellato"<<std::endl;
}

std::string Consumable::exp() { return Obj::exp(); }