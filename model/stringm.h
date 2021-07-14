#ifndef STRINGM_H
#define STRINGM_H

#include <string>
#include "exceptions.h"

namespace sm{

std::string substring(std::string s, std::string kw1, std::string kw2);

bool checkKW(std::string s, std::string kw1, std::string kw2);

}

#endif // STRINGM_H
