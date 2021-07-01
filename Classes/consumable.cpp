#include <iostream>
#include <string>
#include "consumable.h"

using namespace std;

Consumable::Consumable(string imported) : Object(imported);

Consumable::~Consumable();

virtual string  Consumable::export() { return Object::export(); };