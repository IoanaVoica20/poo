#pragma once
#include "I_Utilizator.h"
#include "Client.h"

class Factory
{
public:
	static I_Utilizator* getClient(std::vector<std::string> date) {
		return new Client(date);
	}
};

