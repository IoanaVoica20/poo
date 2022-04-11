#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include <vector>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#define SQL_RESULT_LEN 240
#define SQL_RETURN_CODE_LEN 1000

class Data_Access_Layer
{
private:
	static Data_Access_Layer* instance;
	static SQLHANDLE conn;
	static SQLHANDLE stmt;
	static SQLHANDLE env;
	static SQLWCHAR retconnstr[SQL_RETURN_CODE_LEN];

	Data_Access_Layer() {};
	Data_Access_Layer(const Data_Access_Layer&) {};
	~Data_Access_Layer() {};
	static void cancelDB();
	static void allocDB();

public:
	
	static Data_Access_Layer& getInstance();
	static void destroyInstance();
	static std::string SELECT(std::string);
	static void INSERT(std::string);
	static void ERASE(std::string);
	
};
