#include "A_Utilizator.h"
#include "Data_Access_Layer.h"

A_Utilizator::A_Utilizator(std::vector<std::string> date)
{
	username = date[0];
	parola = date[1];
	nume = date[2];
	prenume = date[3];
	email = date[4];
	adresa = date[5];
	telefon = date[6];
	statut = date[7];
	if (date.size() > 8)
	{
		numeCompanie = date[8];
		telCompanie = date[9];
		departament = date[10];
	}
	else {
		numeCompanie = "";
		telCompanie = "";
		departament = "";
	}
}

bool A_Utilizator::verificaParola(std::string p)
{
	std::string query = "SELECT Parola FROM Conturi WHERE Username = '";
	query += username;
	query += "'";

	std::string parola = Data_Access_Layer::getInstance().SELECT(query);
	if (parola == p)
		return true;
	return false;
}

bool A_Utilizator::verificaUsername(std::string u)
{
	std::string query = "SELECT ID_Client FROM Conturi WHERE Username = '";
	query += u;
	query += "'";

	std::string un =Data_Access_Layer::getInstance().SELECT(query);

	if (un.length()<5)
		return true;
	return false;
}