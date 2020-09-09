#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <thread>
#include <mutex>
#include <WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")

#include "sqlite3.h"
#pragma comment(lib, "sqlite3.lib")

#include "pokemon.h"
#include "battle.h"
#include "strFunction.h"

#define DEFAULT_BUFLEN 1024
#define AUTOFIGHT 1

using namespace std;

class Hub;

class Endpoint
{
private:
	Hub &hub;
	sqlite3 *&db;

	int _PlayerID;
	string _userName;

	string _ip;
	int _port;
	SOCKET endpointSocket;
	SOCKET clientSocket;

	string buf2;

	bool _online;
	bool running;
	//bool timing;
	bool generate_new_pokemon;

	int win_round;
	int total_round;

	mutex endpoint_mute;
public:
	Endpoint(int userId, sqlite3 *&db,Hub &hub);
	~Endpoint();
	// getter
	int getPlayerID()const { return _PlayerID; }
	bool getOnline()const { return _online; }
	int getPort()const { return _port; }
	int getWinRound()const { return win_round; }
	int getTotalRound()const { return total_round; }
	// setter
	void setWinRound(int w) { win_round = w; }
	void setTotalRound(int t) { total_round = t; }

	// 客户端指令处理
	void dealClientInfo(const char* recvbuf);
	void changePokemonName(int pokemonID,string newname);
	void getPokemonList(int PlayerID);
	void changePassword(int PlayerID, const string oldpassword, const string newpassword);
	void getUserList();
	void logOut();
	void savePokemonToDB(const Pokemon &pokemon);
	void getPokemonInfo(int PokemonID);
	void upgradeBattle(int pokemonid_1, int pokemonid_2);
	void changePokemonMaster(int pokemonid, int playerid);
	void losePokemon(int playerid);

	// 控制线程
	void process();
	// 启动endpoint，分配端口号
	int start();
	// 结束endpoint
	//void terminateFunc();
	// endpoint处理线程
	void listenFunc();

	strFunction strfunc;

};

inline int sqlite3_nonusecallback(void* whatever, int argc, char** argv, char **nothing) { return 0; };