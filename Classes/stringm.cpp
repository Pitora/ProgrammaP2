#include "stringm.h"

namespace sm{


std::string substring(std::string s, std::string w1, std::string w2)
{
    size_t pos1 = s.find(w1);
    size_t pos2 = s.find(w2);
    pos1 += w1.length();        //attenzione : legge i bytes che compongono la stringa
    if (pos1 <= pos2)
    {
        return s.substr(pos1,pos2-pos1);
    }
    else throw err_sub();
    return "13";

}

bool checkKW(std::string s, std::string kw1, std::string kw2)
{
    if (s.find(kw1) != size_t(-1) && s.find(kw2) != size_t(-1))
    {
        return true;
    }
    else return false;
}

}