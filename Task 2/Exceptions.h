#pragma once
#include <exception>
#include <string>

using namespace std;

//Common Exceptions
class DLLNotFoundException : public exception {
public:
	virtual const char* what() const throw() {
		return "The Winsock dll was not found!";
	}
};

class InvalidSocketException : public exception {
public:
	virtual const char* what() const throw() {
		return "Invalid Socket!";
	}
};

class SocketErrorException : public exception {
public:
	virtual const char* what() const throw() {
		return "Socket Error occurred!";
	}
};

//Client Exceptions
class ClientFailedToConnectException : public exception {
public:
	virtual const char* what() const throw() {
		return "Client failed to connect! Try checking if the server is running.";
	}
};

class ClientSendException : public exception {
public:
	virtual const char* what() const throw() {
		return "Client failed to send!";
	}
};

//Server Exceptions
class ServerBindingException : public exception {
public:
	virtual const char* what() const throw() {
		return "Server failed to bind!";
	}
};

class ServerSocketListenException : public exception {
public:
	virtual const char* what() const throw() {
		return "Server error listening on socket!";
	}
};

class ServerAcceptConnectionException : public exception {
public:
	virtual const char* what() const throw() {
		return "Server error accepting socket connection!";
	}
};

class ServerSendException : public exception {
public:
	virtual const char* what() const throw() {
		return "Server failed to send!";
	}
};