#pragma once
#include <exception>
#include <string>

using namespace std;

class ExceptionDLLNotFound : public exception {
	public:
		virtual const char* what() const throw() {
			return "Winsock DLL not found!";
		}
};

class SocketErrorException : public exception {
	public:
		virtual const char* what() const throw() {
			return "Socket Error occurred!";
		}
};

class InvalidSocketException : public exception {
	public:
		virtual const char* what() const throw() {
			return "Invalid socket!";
		}
};

class ClientFailedToConnectException : public exception {
	public:
		virtual const char* what() const throw() {
			return "Failed to connect to client, check if server is running";
		}
};

class ClientSendException : public exception {
	public:
		virtual const char* what() const throw() {
			return "Client failed to send!";
		}
};

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