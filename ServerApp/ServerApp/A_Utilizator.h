#pragma once
#include "I_Utilizator.h"
#include "Utile.h"
#include <iostream>
#include <vector>

class A_Utilizator :
    public I_Utilizator
{
protected:
    std::string username;
    std::string parola;

    std::string nume;
    std::string prenume;
    std::string email;
    std::string adresa;
    std::string telefon;
    std::string statut;
    std::string numeCompanie;
    std::string telCompanie;
    std::string departament;
public:
    A_Utilizator(std::string un, std::string pa,std::string n, std::string p, std::string e, std::string a,
        std::string tel, std::string st,std::string nc, std::string tc, std::string de) :username(un),parola(pa), nume(n), prenume(p), email(e), adresa(a), telefon(tel), statut(st),numeCompanie(nc), telCompanie(tc), departament(de) {};
    A_Utilizator(std::vector<std::string> date);
    bool verificaParola(std::string);
    bool verificaUsername(std::string);
};

