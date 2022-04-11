#pragma once
#include <iostream>
#include <winsock.h>
#pragma comment (lib,"Ws2_32.lib")
#include <string.h>
#include "Protocol.h"

class Conectare_Srv
{
	static int nRet;

	static struct sockaddr_in srv;
	//static int indexMeniu;

	Conectare_Srv() noexcept { ; }
	Conectare_Srv(Conectare_Srv& other) noexcept { ; }
	Conectare_Srv(Conectare_Srv&& other) noexcept { ; }
public:
	static int nClientSocket;
	static void Connect();
	static std::string Recvs();
	static void SendToServer(const char*);
	
};

