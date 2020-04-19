#include "stdafx.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include "Comms.h";
#include "Exceptions.h";

int Comms::SetupWinsock() {
	try {
		WSADATA wsaData;
		int wsaerr;
		WORD wVersionRequested = MAKEWORD(2, 2);
		wsaerr = WSAStartup(wVersionRequested, &wsaData);
		if (wsaerr != 0) {
			throw DLLNotFoundException();
		}
		else {
			cout << "The Winsock dll found!" << endl;
			cout << "Winsock status: " << wsaData.szSystemStatus << endl;
			return 1;
		};
	}
	catch (DLLNotFoundException& e) {
		PrintException(e.what());
	}
};

int Comms::SetupSocket() {
	try {
		SOCKET instanceSocket = INVALID_SOCKET;
		instanceSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (instanceSocket == INVALID_SOCKET) {
			int errorCode = WSAGetLastError();
			throw InvalidSocketException();
			WSACleanup();
		}
		else {
			cout << "socket() is OK!" << endl;
			return instanceSocket;
		}
	}
	catch (InvalidSocketException& e) {
		PrintException(e.what());
	}
}

sockaddr_in Comms::SetupService() {
	int port = 55555;
	sockaddr_in service;
	service.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
	service.sin_port = htons(port);
	return service;
}

int Comms::EndSession() {
	system("pause");
	WSACleanup();
	return 0;
};