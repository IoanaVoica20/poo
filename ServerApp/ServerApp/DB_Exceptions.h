#pragma once
#include "A_Exceptions.h"
class DB_Exceptions :
    public A_Exceptions
{
public:
    DB_Exceptions(std::string);
};

