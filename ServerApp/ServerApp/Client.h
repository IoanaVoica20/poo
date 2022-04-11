#pragma once
#include "A_Utilizator.h"
#include <iostream>
#include <vector>

class Client :
    public A_Utilizator
{
public:
    Client(std::vector<std::string> date) :A_Utilizator(date) {};
    std::string getID_Client();
    void adaugaContClientPF();
};
