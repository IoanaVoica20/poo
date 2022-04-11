#include "Client.h"
#include "Data_Access_Layer.h"

std::string Client::getID_Client()
{
	std::string query = "SELECT ID_Client FROM Date_Clienti WHERE Nume = '";
	query += nume;
	query += "' AND Prenume = '";
	query += prenume;
	query += "'";
	return Data_Access_Layer::getInstance().SELECT(query);
}

void Client::adaugaContClientPF()
{
	std::string query = "INSERT INTO Date_Clienti(Nume, Prenume, Email, Adresa, Telefon, Statut, NumeCompanie,TelefonCompanie, Departament) VALUES('";
	query += nume;
	query += "','";
	query += prenume;
	query += "','";
	query += email;
	query += "','";
	query += adresa;
	query += "',";
	query += telefon;
	query += ",'";
	query += statut;
	query += "',";
	query += "NULL,NULL,NULL)\0";
	//std::cout << query << "\n";

	//Data_Access_Layer::getInstance().INSERT(query);
	Data_Access_Layer& db = Data_Access_Layer::getInstance();
	db.INSERT(query);

	
	std::string q = "INSERT INTO [Conturi](ID_Client,Username, Parola) VALUES(";
	q += getID_Client();
	q += ",'";
	q += username;
	q += "','";
	q += parola;
	q += "')";

	db.INSERT(q);
}