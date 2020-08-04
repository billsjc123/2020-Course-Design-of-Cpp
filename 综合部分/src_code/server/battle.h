#pragma once
#include "pokemon.h"
#include <windows.h>

#include "strFunction.h"

#define BATTLETIMEGAP 20
#define DEFAULT_BUFLEN 1024

class BattleController
{
public:
	BattleController(Pokemon &p1, Pokemon &p2,SOCKET &clientSocket,bool autofight);
	//void startBattle();
	int startBattleForClient();

	strFunction strfunc;
private:
	Pokemon &_p1;
	Pokemon &_p2;
	int _autofight;
	int _timer1,_timer2;
	SOCKET _clientSocket;
	string sendbuf;
};