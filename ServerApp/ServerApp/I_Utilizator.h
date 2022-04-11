#pragma once
#include <iostream>

class I_Utilizator
{
public:
	virtual void adaugaContClientPF() = 0;
	virtual std::string getID_Client() = 0;
	virtual bool verificaParola(std::string) = 0;
	virtual bool verificaUsername(std::string) = 0;
};

