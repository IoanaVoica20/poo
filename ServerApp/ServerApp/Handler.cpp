#include "Handler.h"
#include <iostream>
#include <stdlib.h>
#include "Factory.h"
#include "I_Utilizator.h"
#include <vector>
#include <sstream>

std::pair<int, std::vector<std::string>> Handler::proceseaza(std::string msg)
{
	std::pair<int, std::vector<std::string>> p;
	std::string code;
	std::istringstream m(msg);
	
	std::getline(m, code, '$');
	msg.erase(msg.begin(), msg.begin() + code.length()+1);
	p.first = atoi(code.c_str());
	while (1)
	{
		std::istringstream M(msg);
		std::getline(m, code, '$');
		p.second.push_back(code);
		msg.erase(msg.begin(), msg.begin() + code.length()+1);
		if (msg == "")
			break;
	}
	return p;
}

void Handler::interpreteazaMesaj(std::pair<int, std::vector<std::string>> msg)
{
	 
	switch (msg.first) //vezi protocol
	{
	case (1): {
		I_Utilizator* u = Factory::getClient(msg.second);
		u->adaugaContClientPF();
		break;
	}
	default: break;

	}
}