#include "Data_Access_Layer.h"

#include <iostream>

Data_Access_Layer* Data_Access_Layer::instance = nullptr;
SQLHANDLE Data_Access_Layer::conn = nullptr;
SQLHANDLE Data_Access_Layer::stmt = nullptr;
SQLHANDLE Data_Access_Layer::env = nullptr;
SQLWCHAR Data_Access_Layer::retconnstr[SQL_RETURN_CODE_LEN];

Data_Access_Layer& Data_Access_Layer::getInstance()
{
	if (!Data_Access_Layer::instance)
	{
		Data_Access_Layer::instance = new Data_Access_Layer();
	}
	return *Data_Access_Layer::instance;
}

void Data_Access_Layer::destroyInstance()
{
	if (Data_Access_Layer::instance)
	{
		delete Data_Access_Layer::instance;
		Data_Access_Layer::instance = nullptr;
	}
}

void Data_Access_Layer::allocDB()
{
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env))
		Data_Access_Layer::cancelDB();
	if (SQL_SUCCESS != SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
		Data_Access_Layer::cancelDB();
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, env, &conn))
		Data_Access_Layer::cancelDB();
	std::cout << "Attemting connection to SQL Server....\n";
	switch (SQLDriverConnectW(conn, NULL,
		(SQLWCHAR*)L"DRIVER={SQL Server};SERVER=localhost, 1434;DATABASE=Poo;Trusted=true",
		SQL_NTS, retconnstr, 1024, NULL, SQL_DRIVER_NOPROMPT))
	{
	case SQL_SUCCESS:
		std::cout << "Conexiunea la baza de date s-a realizat cu succes.\n";
		break;
	case SQL_SUCCESS_WITH_INFO:
		std::cout << "Conexiunea la baza de date s - a realizat cu succes.\n";
		break;
	case SQL_INVALID_HANDLE:
		std::cout << "Nu s-a putut realiza conexiunea la baza de date.\n";
		break;
	case SQL_ERROR:
		std::cout << "Nu s-a putut realiza conexiunea la baza de date.\n";
		break;
	default:
		break;
	}

	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, conn, &stmt))
		Data_Access_Layer::cancelDB();
}
//"SELECT TOP (10)[CategoryName] FROM [Northwind].[dbo].[Categories]"
std::string Data_Access_Layer::SELECT(std::string query)
{

	Data_Access_Layer::allocDB();
	std::cout << "\nExecuting query...\n";

	std::wstring q(query.length(), L' ');
	std::copy(query.begin(), query.end(), q.begin());

	if (SQL_SUCCESS != SQLExecDirect(stmt, (SQLWCHAR*)q.c_str(), SQL_NTS)) {
		std::cout << "Eroare la efectuare query\n";
		Data_Access_Layer::cancelDB();
	}
	else {

		//declar variabile de output si pointer
		SQLCHAR version[SQL_RESULT_LEN];
		SQLINTEGER ptr;

		//std::cout << "\nQuery result:\n";
		while (SQLFetch(stmt) == SQL_SUCCESS) {
			SQLGetData(stmt, 1, SQL_CHAR, version, SQL_RESULT_LEN, &ptr);


			//std::cout << version << "\n";
		}
		Data_Access_Layer::cancelDB();
		std::string str((const char*)version);
		return str;
	}
	
}

void Data_Access_Layer::INSERT(std::string query)
{
	Data_Access_Layer::allocDB();
	std::cout << "\nExecuting query...\n";

	std::wstring q(query.length(), L' ');
	std::copy(query.begin(), query.end(), q.begin());
	if (SQL_SUCCESS != SQLExecDirect(stmt, (SQLWCHAR*)q.c_str(), SQL_NTS)) {
		std::cout << "Eroare la efectuare query\n";
		Data_Access_Layer::cancelDB();
	}
	std::cout << "Query executed\n";
	Data_Access_Layer::cancelDB();
}

void Data_Access_Layer::ERASE(std::string query)
{
	Data_Access_Layer::allocDB();
	std::cout << "\nExecuting query...\n";

	std::wstring q(query.length(), L' ');
	std::copy(query.begin(), query.end(), q.begin());
	if (SQL_SUCCESS != SQLExecDirect(stmt, (SQLWCHAR*)q.c_str(), SQL_NTS)) {
		std::cout << "Eroare la efectuare query\n";
		Data_Access_Layer::cancelDB();
	}
	std::cout << "Query executed\n";
	Data_Access_Layer::cancelDB();
}

void Data_Access_Layer::cancelDB()
{
	SQLFreeHandle(SQL_HANDLE_STMT, stmt);
	SQLDisconnect(conn);
	SQLFreeHandle(SQL_HANDLE_DBC, conn);
	SQLFreeHandle(SQL_HANDLE_ENV, env);
}
