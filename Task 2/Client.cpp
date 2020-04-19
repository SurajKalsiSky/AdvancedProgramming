#include "stdafx.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include "Client.h"
#include "Exceptions.h";

int Client::Run() {
	SOCKET clientSocket;
	Client client;
	SERVICEPARAMS serviceParams;

	this->SetupWinsock();
	clientSocket = this->SetupSocket();
	sockaddr_in clientService = this->SetupService();
	this->Connect(clientSocket, clientService);

	DWORD threadId;
	cout << "Client is connecting to a host" << endl;
	serviceParams.socket = (LPVOID)clientSocket;
	serviceParams.instance = this;
	serviceParams.size = sizeof(Client);
	serviceParams.name = "Client";

	CreateThread(NULL, 0, this->ClientThreadSender, &serviceParams, 0, &threadId);

	cout << "Messaging session started! Enter your messages below." << endl << endl;

	int byteCount = 0;
	while (true) {
		this->SocketReceiver<SERVICEPARAMS>(serviceParams, (SOCKET)clientSocket, byteCount);
	}

	closesocket(clientSocket);
	return this->EndSession();
}

int Client::Connect(SOCKET clientSocket, sockaddr_in clientService) {
	try {
		if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(Client)) == SOCKET_ERROR) {
			throw ClientFailedToConnectException();
		}
		return 1;
	}
	catch (ClientFailedToConnectException& e) {
		PrintException(e.what());
		WSACleanup();
		exit(0);
	}
}

DWORD WINAPI Client::ClientThreadSender(void* param) {
	SERVICEPARAMS* params = (SERVICEPARAMS*)param;
	SOCKET socket = (SOCKET)params->socket;
	Client client;
	int byteCount;
	bool shouldRun = true;

	try {
		while (shouldRun) {
			Sleep(500);
			if (socket != INVALID_SOCKET) {
				byteCount = send(socket, (char*)&client, sizeof(Client), 0);
				if (byteCount == SOCKET_ERROR) {
					throw ClientSendException();
				}
				else {
					cin >> client.message;
					if (client.message == client.QUIT) {
						shouldRun = false;
						exit(0);
					};
				}
			}
			else {
				throw InvalidSocketException();
			}
		}
		closesocket(socket);
		return 0;
	}
	catch (InvalidSocketException& e) {
		PrintException(e.what());
	}
	catch (ClientSendException& e) {
		PrintException(e.what());
		closesocket(socket);
		return -1;
	}
}