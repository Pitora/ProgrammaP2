#include "character.h"

Character::Character(){}

Character::Character(std::string n, DeepPtr<Weapon> wp, C<DeepPtr<Armor>> armor, C<DeepPtr<Consumable>> inv, int v, int s, int d, int a) : name_build(n),eq_weap(wp),eq_armor(armor),inventory(inv),vit(v),str(s),dex(d),aim(a) {}

Character::Character(std::string imported){
    if (imported.find("<Character>") != -1 && imported.find("</Character>") != -1)
    {
        name_build = Obj::substring(imported, "<NameBuild>", "</NameBuild>");        
        eq_weap = DeepPtr<Weapon>(new Weapon(Obj::substring(imported, "<EqWeap>", "</EqWeap>")));
        std::string s = Obj::substring(imported, "<EqArmor>", "</EqArmor>");
        Armor* a; 
        int i = 0;
        while (s.find("<ArmorP" + std::to_string(i) + '>') != -1 && s.find("</ArmorP" + std::to_string(i) + '>') != -1 )
        {   
            a = new Armor(Obj::substring(s, "<ArmorP" + std::to_string(i) + '>', "</ArmorP" + std::to_string(i) + '>'));
            eq_armor.insertBack(DeepPtr<Armor>(a));
            i++;
        }
        delete a;
        s = Obj::substring(imported, "<Inventory>", "</Inventory>");
        Consumable* c;
        i = 0;
        while (s.find("<Consum" + std::to_string(i) + '>') != -1 && s.find("</Consum" + std::to_string(i) + '>') != -1 )
        {   
            if (s.find("<Healing>") != -1 && s.find("</Healing>") != -1)
            {
                c = new Healing(Obj::substring(s, "<Consum" + std::to_string(i) + '>', "</Consum" + std::to_string(i) + '>'));
            }
            else if (s.find("<Buff>") != -1 && s.find("</Buff>") != -1)
            {
                c = new Buff(Obj::substring(s, "<Consum" + std::to_string(i) + '>', "</Consum" + std::to_string(i) + '>'));
            }
            inventory.insertBack(DeepPtr<Consumable>(c));
            i++;
        }
        delete c;
    }
}

Character::~Character(){
    std::cout<<"Cancellazione personaggio"<<std::endl;
}

Character::Character(const Character& x) : name_build(x.name_build), eq_weap(x.eq_weap), eq_armor(x.eq_armor), inventory(x.inventory) {}

std::string Character::getName() const {
    return name_build;
}

DeepPtr<Weapon> Character::getEqWeap() const {
    return eq_weap;
}

C<DeepPtr<Armor>> Character::getEqArmor() const{
    return eq_armor;
}

C<DeepPtr<Consumable>> Character::getInv() const{
    return inventory;
}

C<int> Character::getStats() const {
    C<int> l;
    l.insertBack(vit);
    l.insertBack(str);
    l.insertBack(dex);
    l.insertBack(aim);
    return l;
}

void Character::setName(std::string s) {
    name_build = s;
}
void Character::setWeap(const DeepPtr<Obj>& w) {
    eq_weap = DeepPtr<Weapon>(dynamic_cast<Weapon*>(w->clone()));
}

void Character::disequip(const DeepPtr<Obj>& r){
    if(dynamic_cast<Armor*>(&(*r)))
    {
        C<DeepPtr<Armor>>::const_iterator i = eq_armor.begin();
        bool found = false;
        while(i != eq_armor.end() && !found)
        {
            if((*i)->getId() == r->getId())
            {
                found = true;
            }
            else{
                i++;
            }
        } 
        if (found)
        {
            eq_armor.remove(*i);
        }
    }
    else if (dynamic_cast<Consumable*>(&(*r)))
    {
        C<DeepPtr<Consumable>>::const_iterator i = inventory.begin();
        bool found = false;
        while(i != inventory.end() && !found)
        {   
            if((*i)->getId() == r->getId())
            {
                found = true;
            }else{
                i++;
            }
        } 
        if (found)
        {
            inventory.remove(*i);
        }
    }
}
void Character::addArmor(const DeepPtr<Obj>& a) {
    eq_armor.insertBack(DeepPtr<Armor>(dynamic_cast<Armor*>(a->clone())));
}

void Character::addConsum(const DeepPtr<Obj>& c) {
    if (Buff* b = dynamic_cast<Buff*>(&(*c)))
    {
        inventory.insertBack(DeepPtr<Consumable>(b->clone()));  
    }
    else if (Healing* h = dynamic_cast<Healing*>(&(*c)))
    {
        inventory.insertBack(DeepPtr<Consumable>(h->clone()));
    }
}

void Character::setVit(int x){vit = x;}

void Character::setStr(int x){str = x;}

void Character::setDex(int x){dex = x;}

void Character::setAim(int x){aim = x;}


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



std::string Character::exp() const{       
    std::string s = "<Character>";
    s += "<NameBuild>" + name_build + "</NameBuild>";
    s += "<EqWeap>" + (*eq_weap).exp() + "</EqWeap>";
    int c = 0;
    s += "<EqArmor>";
    for (C<DeepPtr<Armor>>::const_iterator i = eq_armor.begin(); i != eq_armor.end(); ++i)
    {   
        s += "<ArmorP" + std::to_string(c) + '>';
        s += (*i)->exp();
        s += "</ArmorP" + std::to_string(c) + '>';
        c++;
    }
    s += "</EqArmor>";
    c = 0;
    s += "<Inventory>";
    for (C<DeepPtr<Consumable>>::const_iterator i = inventory.begin(); i != inventory.end(); ++i)
    {   
        s += "<Consum" + std::to_string(c) + '>';
        s += (*i)->exp();
        s += "</Consum" + std::to_string(c) + '>';
        c++;
    }
    s += "</Inventory>";
    s += "</Character>";
    return s;
}

//void Character::import(string imported){       

//} 