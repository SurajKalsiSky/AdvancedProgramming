#pragma once
#include <string>
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "stdafx.h"
#include "Exceptions.h";

using namespace std;

class Comms {
	public:
		string message;
		const string QUIT = "QUIT";
		template<typename T>
		void SocketReceiver(T instance, SOCKET socket, int byteCount);
		virtual int SetupWinsock();
		virtual int SetupSocket();
		virtual sockaddr_in SetupService();
		virtual int EndSession();
		static void PrintException(string msg) {
			cout << "Error: " << msg << endl;
		}
};

template <typename T>
inline void Comms::SocketReceiver(T params, SOCKET socket, int byteCount) {
	try {
		if (socket != INVALID_SOCKET) {
			byteCount = recv(socket, (char*)params.instance, params.size, 0);
			if (byteCount == SOCKET_ERROR) {
				throw SocketErrorException();
			} else {
				if (params.instance->message != "") {
					cout << params.name << ": " << params.instance->message << endl;
				}
			}
		} else {
			throw InvalidSocketException();
		}
	} catch (InvalidSocketException& e) {
		PrintException(e.what());
	} catch (SocketErrorException& e) {
		PrintException(e.what());
		closesocket(socket);
		exit(0);
	}
}