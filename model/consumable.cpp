#include "consumable.h"

Consumable::Consumable() {}

Consumable::Consumable(int i, std::string n) : Obj(i,n) {}

Consumable::Consumable(std::string imported) : Obj(imported) {}

Consumable::~Consumable() {
    //std::cout<<"Consumabile cancellato"<<std::endl;
}


Consumable* Consumable::clone() const {return new Consumable(*this);}

void Consumable::print(std::ostream& os) const { Obj::print(os);}

std::string Consumable::exp() const { return Obj::exp(); }

std::string Consumable::getInfo() const {return Obj::getInfo(); }
