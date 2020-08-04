#include "battle.h"

BattleController::BattleController(Pokemon &p1, Pokemon &p2,SOCKET &clientSocket,bool autofight):_p1(p1),_p2(p2),_clientSocket(clientSocket)
{
	// 因为speed与攻击次数成正比，speed越大减为0需要的时间越久，因此timer设置为对手的speed
	_timer1 = p2.speed(), _timer2 = p1.speed();
	_autofight = autofight;
}

//void BattleController::startBattle()
//{
//	cout << "--------------------------------------------战斗开始--------------------------------------------\n";
//	cout << _p1.name() << "和" << _p2.name() << "之间的战斗一触即发！\n";
//	// 初始化战斗属性
//	_p1.restoreAll();
//	_p2.restoreAll();
//
//	// 双方轮流出招,一方HP为0时停止
//	while (_p1.battleHp() && _p2.battleHp())
//	{
//		_timer1--, _timer2--;
//		if (!_timer1)
//		{
//			_p1.attack(_p2, _autofight);
//			_timer1 = _p2.battleSpeed();
//		}
//		if (!(_p1.battleHp() && _p2.battleHp()))
//			break;
//		if (!_timer2)
//		{
//			_p2.attack(_p1, _autofight);
//			_timer2 = _p1.battleSpeed();
//		}
//		Sleep(BATTLETIMEGAP);
//	}
//	// 某一方HP为0
//	if (!_p1.battleHp())
//	{
//		cout << _p1.name() << "被一拳揍飞！\n";
//		cout << _p2.name() << "击败了" << _p1.name() << "!\n";
//		// 经验结算
//		cout << "--------------------------------------------经验结算--------------------------------------------\n";
//		int baseEP = 30, levelEP = abs(_p1.ep() - _p2.ep()) / 10;
//		_p2.gainEp(baseEP + levelEP);
//		_p1.gainEp(levelEP);
//	}
//	else
//	{
//		cout << _p2.name() << "昏迷不醒！\n";
//		cout << _p1.name() << "战胜了" << _p2.name() << "!\n";
//		// 经验结算
//		cout << "--------------------------------------------经验结算--------------------------------------------\n";
//		int baseEP = 30, levelEP = abs(_p1.ep() - _p2.ep()) / 10;
//		_p1.gainEp(baseEP + levelEP);
//		_p2.gainEp(levelEP);
//	}
//	cout << "--------------------------------------------战斗结束--------------------------------------------\n";
//
//}

/*
* 战斗通信格式
* <PlayerRound 0|1|2>
* <skillName>
* <dodge 0|1>
* <critical strike 0|1> + '\n'
* <self>
* <pokemonid> <name> <race>
* <battleatk> <battledfs> <battlehp> <battlespeed> <lv> <maxhp>
* <pp1> <pp2> <pp3> + '\n'
* <opponent>
* <pokemonid> <name> <race>
* <battleatk> <battledfs> <battlehp> <battlespeed> <lv> <maxhp>
* <pp1> <pp2> <pp3>
*/

/*
* 战斗结算格式
* <PlayerRound 3>
* <winner 1|2>
* 
*/
int BattleController::startBattleForClient()
{
	cout << "--------------------------------------------战斗开始--------------------------------------------\n";
	cout << _p1.name() << "和" << _p2.name() << "之间的战斗一触即发！\n";
	
	char recvbuf[DEFAULT_BUFLEN];
	// 初始化战斗属性
	_p1.restoreAll();
	_p2.restoreAll();

	sendbuf = "2\n";
	sendbuf += to_string(_p1.pokemonid()) + ' ' + _p1.name() + ' ' + to_string(_p1.race()) + ' ';
	sendbuf += to_string(_p1.atk()) + ' ' + to_string(_p1.dfs()) + ' ' + to_string(_p1.hp()) + ' ';
	sendbuf += to_string(_p1.speed()) + ' ' + to_string(_p1.lv()) + ' ' + to_string(_p1.hp()) + ' ';
	sendbuf += to_string(_p1.battlePp(1)) + ' ' + to_string(_p1.battlePp(2)) + ' ' + to_string(_p1.battlePp(2)) + '\n';
	sendbuf += to_string(_p2.pokemonid()) + ' ' + _p2.name() + ' ' + to_string(_p2.race()) + ' ';
	sendbuf += to_string(_p2.atk()) + ' ' + to_string(_p2.dfs()) + ' ' + to_string(_p2.hp()) + ' ';
	sendbuf += to_string(_p2.speed()) + ' ' + to_string(_p2.lv()) + ' ' + to_string(_p2.hp()) + ' ';
	sendbuf += to_string(_p2.battlePp(1)) + ' ' + to_string(_p2.battlePp(2)) + ' ' + to_string(_p2.battlePp(2)) + '\n';

	send(_clientSocket, sendbuf.c_str(), sendbuf.size(), 0);
	recv(_clientSocket, recvbuf, DEFAULT_BUFLEN, 0);
	vector<string> strs = strfunc.split_str(recvbuf, ' ');
	if (strs[0] != "continue")
	{
		cout << recvbuf << endl;
		return 0;
	}

	// 双方轮流出招,一方HP为0时停止
	while (_p1.battleHp() && _p2.battleHp())
	{
		_timer1--, _timer2--;
		if (!_timer1)
		{
			sendbuf = "0 ";
			_p1.attack(_p2, sendbuf,_autofight);
			_timer1 = _p2.battleSpeed();
			cout << sendbuf << endl;
			send(_clientSocket, sendbuf.c_str(), sendbuf.size(), 0);
			recv(_clientSocket, recvbuf, DEFAULT_BUFLEN, 0);
			vector<string> strs = strfunc.split_str(recvbuf, ' ');
			if (strs[0] == "continue" || strs[0] == "end")
			{
			}
			else
			{
				cout << recvbuf << endl;
				return 0;
			}
		}
		if (!(_p1.battleHp() && _p2.battleHp()))
			break;
		if (!_timer2)
		{
			sendbuf = "1 ";
			_p2.attack(_p1, sendbuf,_autofight);
			_timer2 = _p1.battleSpeed();
			cout << sendbuf << endl;
			send(_clientSocket, sendbuf.c_str(), sendbuf.size(), 0);
			recv(_clientSocket, recvbuf, DEFAULT_BUFLEN, 0);
			vector<string> strs = strfunc.split_str(recvbuf, ' ');
			if (strs[0] == "continue" || strs[0] == "end")
			{
			}
			else
			{
				cout << recvbuf << endl;
				return 0;
			}
		}
		Sleep(BATTLETIMEGAP);
		
	}
	string winner, ep1, ep2;
	// 某一方HP为0
	if (!_p1.battleHp())
	{
		cout << _p1.name() << "被一拳揍飞！\n";
		cout << _p2.name() << "击败了" << _p1.name() << "!\n";
		// 经验结算
		cout << "--------------------------------------------经验结算--------------------------------------------\n";
		int baseEP = 30, levelEP = abs(_p1.ep() - _p2.ep()) / 3;
		_p2.gainEp(baseEP + levelEP);
		_p1.gainEp(levelEP);
		winner = '2';
		ep1 = to_string(levelEP);
		ep2 = to_string(baseEP + levelEP);
	}
	else
	{
		cout << _p2.name() << "昏迷不醒！\n";
		cout << _p1.name() << "战胜了" << _p2.name() << "!\n";
		// 经验结算
		cout << "--------------------------------------------经验结算--------------------------------------------\n";
		int baseEP = 30, levelEP = abs(_p1.ep() - _p2.ep()) / 3;
		_p1.gainEp(baseEP + levelEP);
		_p2.gainEp(levelEP);

		winner = '1';
		ep2 = to_string(levelEP);
		ep1 = to_string(baseEP + levelEP);
	}
	//战斗结算
	sendbuf = "3\n";
	sendbuf += winner + ' ' + ep1 + ' ' + ep2;
	send(_clientSocket, sendbuf.c_str(), sendbuf.size(), 0);
	recv(_clientSocket, recvbuf, DEFAULT_BUFLEN, 0);
	strs = strfunc.split_str(recvbuf, ' ');
	if (strs[0] != "end")
	{
		cout << recvbuf << endl;
		return 0;
	}
	cout << "--------------------------------------------战斗结束--------------------------------------------\n";
	
	return atoi(winner.c_str());
	
}