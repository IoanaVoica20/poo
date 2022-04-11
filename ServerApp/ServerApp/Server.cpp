#include "Server.h"
#include "Handler.h"

Server* Server::instance = nullptr;
int Server::nArrClient[5] = { 0 };

Server& Server::getInstance()
{
	if (!Server::instance)
	{
		Server::instance = new Server();
	}
	return *Server::instance;
}

void Server::destroyInstance()
{
	if (Server::instance)
	{
		delete Server::instance;
		Server::instance = nullptr;
	}
}

void Server::ProcesareMesaj(int nClientSocket) {
	std::cout << "\nProcessing the new message for client socket: " << nClientSocket;
	char* buff; //256+1
	buff = (char*)calloc(256, 1);
	//pune mesaj client in buff
	int nRet = recv(nClientSocket, buff, 256, 0);
	if (nRet < 0) {
		std::cout << "\nSometing wrong happend.. closing the connection for the client";
		closesocket(nClientSocket);
		for (int i = 0; i < 5; i++)
			if (nArrClient[i] == nClientSocket) {
				nArrClient[i] = 0;
				break;
			}
	}
	else {
		std::cout << "\nThe message received from the client is: " << buff;
		//send the response to the clinet
		if (strcmp(buff, "HELLOOO"))
			Handler::interpreteazaMesaj(Handler::proceseaza(buff));
			

		send(nClientSocket, "Processed your request", 23, 0);
		std::cout << "\n*****************************************************";
	}
}

void Server::ProcesareCerere() {
	
	if (FD_ISSET(nSocket, &fr)) {
		int nLen = sizeof(struct sockaddr);
		nClientSocket = accept(nSocket, NULL, &nLen);
		if (nClientSocket > 0) {
			//put it into the client fd_set.
			int nIndex;
			for (nIndex = 0; nIndex < 5; nIndex++)
				if (nArrClient[nIndex] == 0) {
					nArrClient[nIndex] = nClientSocket;
					//send(nClientSocket, "CONECTAT", 36, 0); //vezi protocol
					sendMessage("CONECTAT");
					break;
				}
			if (nIndex == 5)
				std::cout << "\nNo space for new connection";

		}

	}
	else
		for (int nIndex = 0; nIndex < 5; nIndex++)
			if (FD_ISSET(nArrClient[nIndex], &fr)) {
				//got a new message from the client
				//just receive
				//queque that for new worker of your server to fulfill the req
				ProcesareMesaj(nArrClient[nIndex]);
			}
}

void Server::sendMessage(const char* msg)
{
	send(nClientSocket, msg, 36, 0);
}

void Server::StartServer() {

	int nRet = 0;
	//intitializare variabilele WSA 
	WSADATA ws;
	if (WSAStartup(MAKEWORD(2, 2), &ws) < 0) {
		std::cout << "WSA faild to initialize";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "WSA initialize..\n";

	//initializare soket
	nSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (nSocket < 0) {
		std::cout << "Soketul nu s-a deshis";
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "Deschis cu succes..\n";

	//initialize the enviroment for sockarddr structure
	srv.sin_family = AF_INET;
	srv.sin_port = htons(PORT);
	srv.sin_addr.s_addr = INADDR_ANY;	//colecteaza adresa ip => nu trebuie sa o introducem
	std::cout << srv.sin_addr.s_addr;
	
	memset(&(srv.sin_zero), 0, 8);



	//Bind the socket to the local port
	nRet = bind(nSocket, (sockaddr*)&srv, sizeof(sockaddr));
	if (nRet < 0) {
		std::cout << "Fail to bind to local port";
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "Successfully to bind to local port\n";

	//Listen the request from client (queques the request)
	nRet = listen(nSocket, 5);
	if (nRet < 0) {
		std::cout << "Fail to start listen to local port";
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "Started listening to local port\n";


	nMaxFd = nSocket;

	struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;

	while (1) {
		FD_ZERO(&fr);
		FD_ZERO(&fw);
		FD_ZERO(&fe);

		FD_SET(nSocket, &fr);
		FD_SET(nSocket, &fe);

		for (int nIndex = 0; nIndex < 5; nIndex++)
			if (nArrClient[nIndex] != 0) {
				FD_SET(nArrClient[nIndex], &fr);
				FD_SET(nArrClient[nIndex], &fe);
			}

		//std::cout << "\nBefore select call: " << fr.fd_count;

		//keep waiting for new request and proceed as per the request

		nRet = select(nMaxFd + 1, &fr, &fw, &fe, &tv);
		if (nRet > 0) {
			//when someone connects or communicates with a message over
			//a dedicated connection
			std::cout << "\n\nData on port...Processing now...";
			//break;
			if (FD_ISSET(nSocket, &fe)) { //vf daca scketul arunca vreo exceptie
				std::cout << "\nAici este o exceptie. Just get away from here";
			}
			else if (FD_ISSET(nSocket, &fw)) {
				std::cout << "\nReady to write something";
			}
			if (FD_ISSET(nSocket, &fr)) {
				std::cout << "\nReady to read something new came up at the port";
			}
			//
			ProcesareCerere();
			//break;
		}
		else if (nRet == 0) {
			//no connection or any comunication request made or you can
			//say that none of the socket descriptors ar ready
			//std::cout << "\nNothing on port: " << PORT;
		}
		else {
			//it failed  and youre application shoud show some 
			std::cout << "I faild...";
			WSACleanup();
			exit(EXIT_FAILURE);
		}
		//std::cout << "\nAfter the select call: " << fr.fd_count;
	}
}

