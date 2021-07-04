#include "character.h"

Character::Character(){}

Character::Character(std::string n, Weapon *wp, C<DeepPtr<Armor>> armor, C<DeepPtr<Consumable>> inv) : name_build(n),eq_weap(wp),eq_armor(armor),inventory(inv){}

Character::~Character(){
    std::cout<<"Cancellazione personaggio"<<std::endl;
}


int Character::scaling(){
    if (true)
    {
        return 1; // Calcolo 
    }else{
        //return calcolo 2
    }
}

int Character::scalingElem(){
//Stessa cosa di scaling
}

std::string Character::exp() {       
    
}

//void Character::import(string imported){       

//} 