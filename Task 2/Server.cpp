#include "stdafx.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include "Server.h"

int Server::Run() {
	SOCKET serverSocket;
	Server server;
	SERVICEPARAMS serviceParams;

	this->SetupWinsock();
	serverSocket = this->SetupSocket();
	this->CreateServiceBinding(serverSocket);
	this->ListenForClient(serverSocket);
	SOCKET acceptSocket = this->AcceptConnection(serverSocket);

	DWORD threadID;
	cout << "Client Connected!" << endl;
	serviceParams.socket = (LPVOID)acceptSocket;
	serviceParams.instance = this;
	serviceParams.size = sizeof(Server);
	serviceParams.name = "Server";

	CreateThread(NULL, 0, this->ServerThreadSender, &serviceParams, 0, &threadID);

	cout << "Messaging session started! Enter your messages below." << endl << endl;

	int byteCount = 0;
	while (true) {
		this->SocketReceiver<SERVICEPARAMS>(serviceParams, (SOCKET)acceptSocket, byteCount);
	}

	closesocket(acceptSocket);
	return this->EndSession();
}

int Server::CreateServiceBinding(SOCKET serverSocket) {
	try {
		sockaddr_in service = this->SetupService();
		if (bind(serverSocket, (SOCKADDR*)&service, sizeof(Server)) == SOCKET_ERROR) {
			throw ServerBindingException();
		}
		return 1;
	}
	catch (ServerBindingException& e) {
		PrintException(e.what());
		closesocket(serverSocket);
		WSACleanup();
	}
}

void Server::ListenForClient(SOCKET serverSocket) {
	try {
		if (listen(serverSocket, 1) == SOCKET_ERROR) {
			throw ServerSocketListenException();
		}
		else {
			cout << "Waiting for a client to connect..." << endl;
		}
	}
	catch (ServerSocketListenException& e) {
		PrintException(e.what());
	}
}

int Server::AcceptConnection(SOCKET socket) {
	try {
		SOCKET acceptSocket = accept(socket, NULL, NULL);
		if (acceptSocket == INVALID_SOCKET) {
			throw ServerAcceptConnectionException();
		}
		return acceptSocket;
	}
	catch (ServerAcceptConnectionException& e) {
		PrintException(e.what());
		return -1;
	}
}

DWORD WINAPI Server::ServerThreadSender(void* param) {
	SERVICEPARAMS* params = (SERVICEPARAMS*)param;
	SOCKET socket = (SOCKET)params->socket;
	Server server;
	int byteCount;
	bool shouldRun = true;

	try {
		while (shouldRun) {
			Sleep(500);
			if (socket != INVALID_SOCKET) {
				byteCount = send(socket, (char*)&server, sizeof(Server), 0);
				if (byteCount == SOCKET_ERROR) {
					throw ServerSendException();
				}
				else {
					cin >> server.message;
					if (server.message == server.QUIT) {
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
	catch (ServerSendException& e) {
		PrintException(e.what());
		closesocket(socket);
		return -1;
	}
}