#include "character.h"

Character::Character(){}

Character::Character(std::string n, DeepPtr<Weapon> wp, C<DeepPtr<Armor>> armor, C<DeepPtr<Consumable>> inv) : name_build(n),eq_weap(wp),eq_armor(armor),inventory(inv){}

Character::~Character(){
    std::cout<<"Cancellazione personaggio"<<std::endl;
}


int Character::damage() const{
    int atk = eq_weap->getAttack();
    int scaleSum = (str*eq_weap->getScalingStr()/100)+(dex*eq_weap->getScalingDex()/100)+(aim*eq_weap->getScalingAim()/100);
    return (atk+scaleSum);
}

int Character::defense() const{
    int def;
    for (auto i = eq_armor.begin(); i != eq_armor.end(); i++){
        def += (*i)->getDefense();
    }
    return def;
}

std::string Character::exp() {       
    
}

//void Character::import(string imported){       

//} 