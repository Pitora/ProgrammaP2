#include<iostream>
#include "object.h"
#include "character.h"
#include "tc.h"
#include "tdeep.h"

using namespace std;

class Collection {

private:

    dList<DeepPtr<Object>> list;
    Character char;      
    
public:

//metodi statici (caricamento al primo avvio, forse import/export se non implementato in character)

};