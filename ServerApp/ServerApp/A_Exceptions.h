#pragma once
#include "I_Exceptions.h"
class A_Exceptions:
    public I_Exceptions
{
protected:
    int code = 0;
    std::string message;
public:
    int getCode() { return code; };
    std::string getMessage() { return message; };

};

