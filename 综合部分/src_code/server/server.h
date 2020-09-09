#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <conio.h>
#include <thread>
#include <mutex>

#include "endpoint.h"
#include "strFunction.h"

#include <WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")

#include "sqlite3.h"
#pragma comment(lib, "sqlite3.lib")

#include "pokemon.h"

#define DEFAULT_BUFLEN 1024

using namespace std;

class Hub
{
private:
	const int HUB_PORT = 8888;
	SOCKET hubSocket;
	SOCKET clientSocket;
	
	vector<Endpoint *> endpoints;

	char buf[DEFAULT_BUFLEN];

	sqlite3 *db;

	mutex hub_mute;

	// ¼àÌýÏß³Ì
	bool running;
	void ListenFunc();
	void TerminateFunc();

public:
	void dealClientInfo(const string &recv);
	void run();
	void endpointHandler(Endpoint *const endpoint);

	Hub() {};

	strFunction strfunc;

};

//inline int sqlite3_nonusecallback(void* whatever, int argc, char** argv, char **nothing) { return 0; };