#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Server.h"
#include "Data_Access_Layer.h"
#include "Client.h"
#include "I_Utilizator.h"

int main()
{
    Server& srv = Server::getInstance();
    srv.StartServer();
    /*std::string ms = "ion&gheorghe";
    ms.erase(ms.begin(), ms.begin() + sizeof("ion"));
    std::cout << ms;*/
   
    //Data_Access_Layer::getInstance().SELECT("SELECT TOP (10)[CategoryName] FROM [Northwind].[dbo].[Categories]");
    //Data_Access_Layer::getInstance().INSERT("INSERT INTO Clienti(Nume, Prenume, Email,Adresa, Telefon, Statut, NumeCompanie,TelefonCompanie, Departament) VALUES('Ion', 'Gheorghe', 'ion@gh', 'Ro ag B t  503 20', '0754649523', 'client', NULL, NULL, NULL)");
    //Data_Access_Layer::getInstance().ERASE("DELETE FROM [Conturi] WHERE ID_Client = 14");
    //Data_Access_Layer::getInstance().ERASE("DELETE FROM [Date_Clienti] WHERE ID_Client = 14");
    //I_Utilizator* u = new Client("ionpop","hash","pop", "ion", "pop@ion", "arges", "0754649523", "client");
    //u->adaugaContClientPF();
   
    /*if (u->verificaParola("Hash") == true)
        std::cout << "\nTRUE\n";
    else std::cout << "\nFALSE\n";*/
    
    
    /*if (u->verificaUsername("ion") == true)
        std::cout << "\nUsername existent in baza\n";
    else std::cout << "\nUsername-ul nu exista in baza\n";*/
}
