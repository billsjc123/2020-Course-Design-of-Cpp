#include "battle.h"

BattleController::BattleController(Pokemon &p1, Pokemon &p2,SOCKET &clientSocket,bool autofight):_p1(p1),_p2(p2),_clientSocket(clientSocket)
{
	// ��Ϊspeed�빥�����������ȣ�speedԽ���Ϊ0��Ҫ��ʱ��Խ�ã����timer����Ϊ���ֵ�speed
	_timer1 = p2.speed(), _timer2 = p1.speed();
	_autofight = autofight;
}

//void BattleController::startBattle()
//{
//	cout << "--------------------------------------------ս����ʼ--------------------------------------------\n";
//	cout << _p1.name() << "��" << _p2.name() << "֮���ս��һ��������\n";
//	// ��ʼ��ս������
//	_p1.restoreAll();
//	_p2.restoreAll();
//
//	// ˫����������,һ��HPΪ0ʱֹͣ
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
//	// ĳһ��HPΪ0
//	if (!_p1.battleHp())
//	{
//		cout << _p1.name() << "��һȭ��ɣ�\n";
//		cout << _p2.name() << "������" << _p1.name() << "!\n";
//		// �������
//		cout << "--------------------------------------------�������--------------------------------------------\n";
//		int baseEP = 30, levelEP = abs(_p1.ep() - _p2.ep()) / 10;
//		_p2.gainEp(baseEP + levelEP);
//		_p1.gainEp(levelEP);
//	}
//	else
//	{
//		cout << _p2.name() << "���Բ��ѣ�\n";
//		cout << _p1.name() << "սʤ��" << _p2.name() << "!\n";
//		// �������
//		cout << "--------------------------------------------�������--------------------------------------------\n";
//		int baseEP = 30, levelEP = abs(_p1.ep() - _p2.ep()) / 10;
//		_p1.gainEp(baseEP + levelEP);
//		_p2.gainEp(levelEP);
//	}
//	cout << "--------------------------------------------ս������--------------------------------------------\n";
//
//}

/*
* ս��ͨ�Ÿ�ʽ
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
* ս�������ʽ
* <PlayerRound 3>
* <winner 1|2>
* 
*/
int BattleController::startBattleForClient()
{
	cout << "--------------------------------------------ս����ʼ--------------------------------------------\n";
	cout << _p1.name() << "��" << _p2.name() << "֮���ս��һ��������\n";
	
	char recvbuf[DEFAULT_BUFLEN];
	// ��ʼ��ս������
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

	// ˫����������,һ��HPΪ0ʱֹͣ
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
	// ĳһ��HPΪ0
	if (!_p1.battleHp())
	{
		cout << _p1.name() << "��һȭ��ɣ�\n";
		cout << _p2.name() << "������" << _p1.name() << "!\n";
		// �������
		cout << "--------------------------------------------�������--------------------------------------------\n";
		int baseEP = 30, levelEP = abs(_p1.ep() - _p2.ep()) / 3;
		_p2.gainEp(baseEP + levelEP);
		_p1.gainEp(levelEP);
		winner = '2';
		ep1 = to_string(levelEP);
		ep2 = to_string(baseEP + levelEP);
	}
	else
	{
		cout << _p2.name() << "���Բ��ѣ�\n";
		cout << _p1.name() << "սʤ��" << _p2.name() << "!\n";
		// �������
		cout << "--------------------------------------------�������--------------------------------------------\n";
		int baseEP = 30, levelEP = abs(_p1.ep() - _p2.ep()) / 3;
		_p1.gainEp(baseEP + levelEP);
		_p2.gainEp(levelEP);

		winner = '1';
		ep2 = to_string(levelEP);
		ep1 = to_string(baseEP + levelEP);
	}
	//ս������
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
	cout << "--------------------------------------------ս������--------------------------------------------\n";
	
	return atoi(winner.c_str());
	
}