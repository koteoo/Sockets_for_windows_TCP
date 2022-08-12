// Client_TCP.cpp
#include "pch.h"
#include <iostream>
#include <Winsock2.h>
#include <WS2tcpip.h>
#pragma comment(lib,"Ws2_32.lib")
using namespace std;

#define MESSAGE_BUFFER 1024
#define PORT 7777

SOCKET sockd;
sockaddr_in serveraddress;
char message[MESSAGE_BUFFER],message2[MESSAGE_BUFFER];
int errState;
WSAData wsadata;

void processRequest() {
	
	errState = WSAStartup(MAKEWORD(2,2),&wsadata);
	if (errState!=0) {
		cout << "Error WinSock version initializaion #";
		cout << WSAGetLastError();
		exit(1);
	}


	sockd = socket(AF_INET,SOCK_STREAM,0);
	
	if (sockd == INVALID_SOCKET) {
		cout << "Error initialization socket # " << WSAGetLastError() << endl;
		closesocket(sockd);
		WSACleanup();
		exit(1);
	}
	else {
		cout << "Client socket initialization is OK" << endl;
	}

	ZeroMemory(&serveraddress, sizeof(serveraddress));

	inet_pton(AF_INET, "127.0.0.1", &serveraddress.sin_addr.s_addr);
	serveraddress.sin_port = htons(PORT);
	serveraddress.sin_family = AF_INET;

	errState = connect(sockd, (sockaddr*)&serveraddress,sizeof(serveraddress));

	if (errState != 0) {
		cout << "Connection with the server failed!" << endl;
		closesocket(sockd);
		WSACleanup();
		exit(1);
	}
	else {
		cout << "Connection is Established!" << endl;
	}




	cout << "Enter message to the server: ";
	cin >> message;
	send(sockd, message, sizeof(message), 0);

	recv(sockd, message2, sizeof(message2), 0);
	cout << "Data received from server: " << message2 << endl;

	closesocket(sockd);
	WSACleanup();

}

int main()
{
	cout<<"Client TCP:"<<endl;
	processRequest();
}
