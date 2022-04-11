#pragma once
#include <iostream>

class I_Exceptions
{
public:
	virtual int getCode() = 0;
	virtual std::string getMessage() = 0;

};

