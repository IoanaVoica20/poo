#include "DB_Exceptions.h"

DB_Exceptions::DB_Exceptions(std::string msg)
{
	message = msg;
	code = 101;
}