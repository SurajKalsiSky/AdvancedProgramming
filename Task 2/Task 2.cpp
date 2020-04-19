#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <iostream>
#include "pch.h"
#include "Server.h"
#include "Client.h"

#define SERVER false

using namespace std;

int main() {
	cout << "Starting the C++ messaging app!" << endl;
	cout << "Type 'QUIT' at any time to terminate the programs." << endl << endl;
	if (SERVER) {
		Server server;
		server.Run();
	}
	else {
		Client client;
		client.Run();
	}
}
