#include "consumable.h"

Consumable::Consumable() {}

Consumable::Consumable(string imported) : Object(imported) {}

Consumable::~Consumable() {
    std::cout<<"Consumabile cancellato"<<std::endl;
}

string Consumable::exp() { return Obj::exp(); }