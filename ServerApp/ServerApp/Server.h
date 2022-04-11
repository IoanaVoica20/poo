#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include  <iostream>
#pragma comment (lib,"Ws2_32.lib")

#include <winsock2.h>
#define PORT 9909
#ifndef FD_SETSIZE
#define FD_SETSIZE 64
#endif 
#include "Protocol.h"

class Server
{
	static Server* instance;
	Server() {};
	Server(const Server&) {};
	~Server() {};

	struct sockaddr_in srv;
	fd_set fr, fw, fe;

	int nMaxFd;
	int nSocket;
	int nClientSocket;
	static int nArrClient[5];

	void ProcesareMesaj(int nClientSocket);
	void ProcesareCerere();
public:
	static Server& getInstance();
	static void destroyInstance();
	void StartServer();
	void sendMessage(const char*);
};

