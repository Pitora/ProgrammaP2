#include "stringm.h"

namespace sm{

//Metodo che aata una stringa e due parole chiave contenute in tale stringa, ritorna come stringa il contenuto tra le due parole
std::string substring(std::string s, std::string kw1, std::string kw2)
{
    size_t pos1 = s.find(kw1);
    size_t pos2 = s.find(kw2);
    pos1 += kw1.length();        //attenzione : legge i bytes che compongono la stringa
    if (pos1 <= pos2)
    {
        return s.substr(pos1,pos2-pos1);
    }
    else throw err_sub();
    return "13";

}

//Metodo che data una stringa e due parole chiave, ritorna vero se tali parole sono presenti nella stringa, falso altrimenti
bool checkKW(std::string s, std::string kw1, std::string kw2)  
{
    if (s.find(kw1) != size_t(-1) && s.find(kw2) != size_t(-1))
    {
        return true;
    }
    else return false;
}

}
