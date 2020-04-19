#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "stdafx.h"
#include "pch.h"
#include "Server.h"
#include "Client.h"

#define SERVER false // set to true or false to create executables

using namespace std;

int main() {
	cout << "Starting messaging app" << endl;
	cout << "Type 'QUIT' at any time to terminate the programs" << endl << endl;
	if (SERVER) {
		Server server;
		server.Run();
	} else {
		Client client;
		client.Run();
	}
}
