#define _CRT_SECURE_NO_WARNINGS
#include "Conectare_Srv.h"
#include <string.h>

int Conectare_Srv::nRet = 0;
int Conectare_Srv::nClientSocket = 0;
struct sockaddr_in Conectare_Srv::srv;

void Conectare_Srv::Connect() {
	if (nClientSocket == 0)
	{
		WSADATA ws;
		if (WSAStartup(MAKEWORD(2, 2), &ws) < 0) {
			std::cout << "\nWSASartup failed";
			WSACleanup();
			exit(EXIT_FAILURE);
		}

		nClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		if (nClientSocket < 0) {
			std::cout << "\n socket call failed";
			WSACleanup();
			exit(EXIT_FAILURE);
		}

		srv.sin_family = AF_INET;
		srv.sin_port = htons(PORT);
		srv.sin_addr.s_addr = inet_addr("192.168.1.241");  //trebuie introdusa adresa la care vrem sa ne conectam si Port-ul
		memset(&srv.sin_zero, 0, 8);

		nRet = connect(nClientSocket, (struct sockaddr*)&srv, sizeof(srv));
		if (nRet < 0) {
			std::cout << "\nConnect failed";
			WSACleanup();
			exit(EXIT_FAILURE);
		}
		else {
			std::cout << "\nConnected to the server\n";
			
			SendToServer("HELLOOO");
			char* buff;
			buff = (char*)calloc(256, sizeof(char));
			recv(nClientSocket, buff, 256, 0);
		
		}
		
	}

}

std::string Conectare_Srv::Recvs()
{
	char buff1[256];
	recv(nClientSocket, buff1, 256, 0);
	std::string a(buff1);

	return a;

}

void Conectare_Srv::SendToServer(const char* aux) {

	send(nClientSocket, aux, 256, 0);
}

