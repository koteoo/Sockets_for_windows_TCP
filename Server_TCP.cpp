// Server_TCP.cpp

#include "pch.h"
#include <iostream>
#include <Winsock2.h>
#include <WS2tcpip.h>
#pragma comment(lib,"Ws2_32.lib")
using namespace std;

#define MESSAGE_BUFFER 1024
#define PORT 7777

SOCKET sockd,clientd;
struct sockaddr_in serveraddress, client;
int errState;
char message[MESSAGE_BUFFER], message2[MESSAGE_BUFFER];
WSAData wsadata;


void processRequest() {
	//--------Checking of systems Windows ------
	errState = WSAStartup(MAKEWORD(2,2),&wsadata);

	if (errState != 0) {
		cout << "Error WinSock version initializaion #";
		cout << WSAGetLastError();
		exit(1);
	}
	//------------------------------------------

	//------- Creating of the Socket ----------
	sockd = socket(AF_INET,SOCK_STREAM,0);

	if (sockd == INVALID_SOCKET) {
		cout << "Error initialization socket # " << WSAGetLastError() << endl;
		closesocket(sockd);
		WSACleanup();
		exit(1);
	}
	else {
		cout << "Server socket initialization is OK" << endl;
	}
	//------------------------------------------

	ZeroMemory(&serveraddress, sizeof(serveraddress));
	//-------- The filling into a struct of the serveraddress ---------
	serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddress.sin_port = htons(PORT);
	serveraddress.sin_family = AF_INET;
	//-----------------------------------------------------------------


	//-------------- Sock's binding -----------------------------------
	errState = bind(sockd, (sockaddr*)&serveraddress,sizeof(serveraddress));

	if (errState != 0) {
		cout << "Error initialization socket # " << WSAGetLastError() << endl;
		closesocket(sockd);
		WSACleanup();
		exit(1);
	} else {
		cout << "Binding socket to the Server is OK" << endl;
	}
	//-----------------------------------------------------------------


	//------------ Listening ---------------------------
	errState = listen(sockd, SOMAXCONN);
	if (errState != 0) {
		cout << "Can't start to listen to. Error # " << WSAGetLastError() << endl;
		closesocket(sockd);
		WSACleanup();
		exit(1);
	}
	else {
		cout << "Listening..." << endl;
	}
	//--------------------------------------------------
	
	ZeroMemory(&client, sizeof(client));
	int length = sizeof(client);

	//---------------- Connection ----------------------
	clientd = accept(sockd, (sockaddr*)&client, &length);

	if (clientd == INVALID_SOCKET) {
		cout << "Error initialization client socket # " << WSAGetLastError() << endl;
		closesocket(sockd);
		closesocket(clientd);
		WSACleanup();
		exit(1);
	}
	else {
		cout << "Client socket initialization is OK" << endl;
	}
	//--------------------------------------------------

	//--- Recieving and sending of messages ------------
	recv(clientd, message2, sizeof(message2),0);
	cout << "Data received from client: " << message2 << endl;
	
	cout << "Enter message to the client: ";
	cin >> message;
	send(clientd, message, sizeof(message), 0);
	//--------------------------------------------------

	closesocket(clientd);
	closesocket(sockd);
	WSACleanup();

}


int main()
{
	cout << "Server TCP:" << endl;
	processRequest();
}

