#include "character.h"

Character::Character(){}

Character::Character(std::string n, DeepPtr<Weapon> wp, C<DeepPtr<Armor>> armor, C<DeepPtr<Consumable>> inv, int v, int s, int d, int a) : name_build(n),eq_weap(wp),eq_armor(armor),inventory(inv),vitality(v),strenght(s),dexterity(d),aim(a) {}

Character::Character(std::string imported){
    if (sm::checkKW(imported, "<Character>","</Character>"))
    {
        if (sm::checkKW(imported, "<NameBuild>","</NameBuild>"))
        {
            name_build = sm::substring(imported, "<NameBuild>", "</NameBuild>");
        }else throw err_import();
        if (sm::checkKW(imported, "<EqWeap>","</EqWeap>"))
        {
            if (sm::checkKW(imported, "<Melee>", "</Melee>"))
            {
                eq_weap = DeepPtr<Weapon>(new Melee(sm::substring(imported, "<EqWeap>", "</EqWeap>")));
            }
            else if (sm::checkKW(imported, "<Ranged>", "</Ranged>"))
            {
                eq_weap = DeepPtr<Weapon>(new Ranged(sm::substring(imported, "<EqWeap>", "</EqWeap>")));
            }
        }else throw err_import();       
        
        std::string s = sm::substring(imported, "<EqArmor>", "</EqArmor>");
        Armor* a; 
        int i = 0;
        while (sm::checkKW(s, "<ArmorP" + std::to_string(i) + '>',"</ArmorP" + std::to_string(i) + '>'))
        {   
            a = new Armor(sm::substring(s, "<ArmorP" + std::to_string(i) + '>', "</ArmorP" + std::to_string(i) + '>'));
            eq_armor.insertBack(DeepPtr<Armor>(a));
            i++;
        }
        delete a;
        s = sm::substring(imported, "<Inventory>", "</Inventory>");
        Consumable* c;
        i = 0;
        std::string s2;
        while (sm::checkKW(s, "<Consum" + std::to_string(i) + '>', "</Consum" + std::to_string(i) + '>'))
        {   
            s2 = sm::substring(s,"<Consum" + std::to_string(i) + '>',"</Consum" + std::to_string(i) + '>');

            if (sm::checkKW(s2, "<Healing>", "</Healing>"))
            {
                c = new Healing(s2);
            }
            else if (sm::checkKW(s2, "<Buff>", "</Buff>"))
            {
                c = new Buff(s2);
            }
            inventory.insertBack(DeepPtr<Consumable>(c));
            i++;
        }
        delete c;

        if(sm::checkKW(imported, "<Stats>", "</Stats>"))
        {
            s = sm::substring(imported, "<Stats>","</Stats>");
            vitality = stoi(sm::substring(s,"<Vit>","</Vit>"));
            strenght = stoi(sm::substring(s,"<Str>","</Str>"));
            dexterity = stoi(sm::substring(s,"<Dex>","</Dex>"));
            aim = stoi(sm::substring(s,"<Aim>","</Aim>"));
        }else throw err_import();
    }else throw err_import();
}

Character::~Character(){
    std::cout<<"Cancellazione personaggio"<<std::endl;
}

Character::Character(const Character& x) : name_build(x.name_build), eq_weap(x.eq_weap), eq_armor(x.eq_armor), inventory(x.inventory), vitality(x.vitality), strenght(x.strenght), dexterity(x.dexterity), aim(x.aim) {}

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
    l.insertBack(vitality);
    l.insertBack(strenght);
    l.insertBack(dexterity);
    l.insertBack(aim);
    return l;
}

void Character::setName(std::string s) {
    name_build = s;
}

void Character::setWeap(const DeepPtr<Obj>& w) {
    if (dynamic_cast<Weapon*>(&(*w)))
    {
        eq_weap = DeepPtr<Weapon>(dynamic_cast<Weapon*>(w->clone()));
    }else throw err_wrongType();
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
        }else throw err_notFound();
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
        }else throw err_notFound();
    }else throw err_disequip();
}

void Character::changeArmorEq(const DeepPtr<Obj>& a){
    if(dynamic_cast<Armor*>(&(*a)))
    {
        Armor* a2 = dynamic_cast<Armor*>(&(*a));
        C<DeepPtr<Armor>>::const_iterator i = eq_armor.begin();
        bool found = false;
        while(i != eq_armor.end() && !found)
        {
            if((*i)->getArmorType() == a2->getArmorType())
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
            addArmor(a);
        }else throw err_notFound();
    }
}

void Character::addArmor(const DeepPtr<Obj>& a) {
    if (dynamic_cast<Armor*>(&(*a)))
    {
        eq_armor.insertBack(DeepPtr<Armor>(dynamic_cast<Armor*>(a->clone())));
    }else throw err_wrongType();
}

void Character::addConsum(const DeepPtr<Obj>& c) {
    if (Buff* b = dynamic_cast<Buff*>(&(*c)))
    {
        inventory.insertBack(DeepPtr<Consumable>(new Buff(*b)));  
    }
    else if (Healing* h = dynamic_cast<Healing*>(&(*c)))
    {
        inventory.insertBack(DeepPtr<Consumable>(new Healing(*h)));
    }else throw err_wrongType();
}

void Character::setVit(int x){vitality = x;}

void Character::setStr(int x){strenght = x;}

void Character::setDex(int x){dexterity = x;}

void Character::setAim(int x){aim = x;}

bool Character::isRemovingEq(int id) const
{
    if (eq_weap->getId() == id)
    {
        return true;
    }
    for (C<DeepPtr<Armor>>::const_iterator i = eq_armor.begin(); i != eq_armor.end(); ++i)
    {
        if ((*i)->getId() == id)
        {
            return true;
        }
    }

    for (C<DeepPtr<Consumable>>::const_iterator i = inventory.begin(); i != inventory.end(); ++i)
    {
        if ((*i)->getId() == id)
        {
            return true;
        }
    }

    return false;
}

int Character::damage() const{
    int atk = eq_weap->getAttack();
    int scaleSum = (strenght*eq_weap->getScalingStr()/10)+(dexterity*eq_weap->getScalingDex()/10)+(aim*eq_weap->getScalingAim()/10);
    return (atk+scaleSum);
}

int Character::defense() const{
    int def = 0;
    for (auto i = eq_armor.begin(); i != eq_armor.end(); i++){
        def += (*i)->getDefense();
    }
    return (def+vitality/10);
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
    s += "<Stats>";
    s += "<Vit>" + std::to_string(vitality) + "</Vit>";
    s += "<Str>" + std::to_string(strenght) + "</Str>";
    s += "<Dex>" + std::to_string(dexterity) + "</Dex>";
    s += "<Aim>" + std::to_string(aim) + "</Aim>";
    s += "</Stats>";
    s += "</Character>";
    return s;
}

//void Character::import(string imported){       

//} 
