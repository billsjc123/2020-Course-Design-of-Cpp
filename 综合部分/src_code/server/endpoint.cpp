#include "endpoint.h"

Endpoint::Endpoint(int userId, sqlite3 *&database,Hub &hub):_PlayerID(userId),db(database),hub(hub)
{
	_port = 0;
	_online = true;
}

Endpoint::~Endpoint()
{
	closesocket(endpointSocket);
	closesocket(clientSocket);
	if (_port)
	{
		cout << "Endpoint[" << _PlayerID << "]:stop at port " <<_port<< endl;
	}
}

int Endpoint::start()
{
	// �����ݿ��ȡ�û���
	srand((unsigned)time(NULL));
	char **sqlResult;
	int nRow, nColumn;
	string sql = "SELECT username FROM Login WHERE id = "+to_string(_PlayerID)+" ;";
	char *errMsg;
	if(sqlite3_get_table(db, sql.c_str(), &sqlResult, &nRow, &nColumn, &errMsg)!=SQLITE_OK)
	{
		cout << "Endpoint["<< _PlayerID <<"]: Sqlite3 error: " << errMsg << endl;
		sqlite3_free(errMsg);
		return 0;
	}
	else if (nRow == 0)
	{
		cout << "Endpoint[" << _PlayerID << "]: Database content error: Invalid userid or user's information lost!"<<errMsg << endl;
		sqlite3_free_table(sqlResult);
		return 0;
	}
	else
	{
		_userName = sqlResult[1];
		sqlite3_free_table(sqlResult);
	}

#pragma region init sock
	// ��ʼ��Wincock
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		cout << "WSAStartup failed: " << iResult << endl;
		return 0;
	}
	endpointSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	/**
	 * �����ȡ�˿ںŵķ���
	 * ��bind֮ǰ��socket��ַ��sin_port����Ϊ0��������ϵͳ����˿�
	 * ����connect֮����ֱ����sin_port����ȡ�˿ں�
	 * ����ͨ��getsockname()��õ�ǰ�Ѿ���ϵͳbind�˵Ķ˿ںŵĵ�ַ
	*/

	sockaddr_in endpointAddr;
	endpointAddr.sin_family = PF_INET;
	// ����˿ڵ����񽻸�OS
	endpointAddr.sin_port = htons(0);
	endpointAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	cout << "Endpoint[" << _PlayerID << "]:Socket binding...\n";

	if (::bind(endpointSocket, (sockaddr*)&endpointAddr, sizeof(endpointAddr)) == SOCKET_ERROR)
	{
		cout << "bind failed with error: " << WSAGetLastError() << endl;
		closesocket(endpointSocket);
		WSACleanup();
		return 0;
	}
	cout << "Done...\n";
	
	// ����ʹ��getsockname()���õ��˿ں�
	int namelen = sizeof(endpointAddr);
	getsockname(endpointSocket, (sockaddr*)&endpointAddr, &namelen);
	_port = ntohs(endpointAddr.sin_port);

	cout << "Endpoint[" << _PlayerID << "]:Socket listening...\n";

	if (listen(endpointSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		cout << "listen failed with error: " << WSAGetLastError() << endl;
		closesocket(endpointSocket);
		WSACleanup();
		return 0;
	}
	cout << "Done...\n";

	cout << "Endpoint[" << _PlayerID << "]is running at port:" << to_string(_port)<<endl;

#pragma endregion

	// ÿ�ο���һ��Endpoint����һ���µ�Pokemon
	// ����������20������
	// ��ѯ�ж��ٸ�ϵͳ����
	sql = "SELECT id FROM Pokemon WHERE id = 0";
	if (sqlite3_get_table(db, sql.c_str(), &sqlResult,&nRow,&nColumn, &errMsg) != SQLITE_OK)
	{
		cout << "Endpoint[" << _PlayerID << "]: sqlite error:" << errMsg << endl;
		sqlite3_free(errMsg);
		//buf2 = "����ϵͳ����ʱ���������ݿ����";
	}
	if (nRow < 20)
		generate_new_pokemon = true;
	if (generate_new_pokemon)
	{
		// ��ø��û�id
		int id = _PlayerID;
		int rand_race = rand() % RACE_NUM;
		Pokemon p(rand_race, "");
		// �����һ��ep
		int rand_ep = rand() % 1501;
		p.gainEp(rand_ep);
		sql = "INSERT INTO Pokemon (userid,name,race,atk,dfs,hp,speed,lv,ep)";
		sql += " VALUES ('" + to_string(0) + "', '" + p.name();
		sql += "', " + to_string(rand_race) + ", " + to_string(p.atk());
		sql += ", " + to_string(p.dfs()) + ", " + to_string(p.hp());
		sql += ", " + to_string(p.speed()) + ", " + to_string(p.lv());
		sql += ", " + to_string(p.ep()) + "); ";
		
		if (sqlite3_exec(db, sql.c_str(), sqlite3_nonusecallback, NULL, &errMsg) != SQLITE_OK)
		{
			cout << "Endpoint[" << _PlayerID << "]: sqlite error:" << errMsg << endl;
			sqlite3_free(errMsg);
			//buf2 =  "����ϵͳ����ʱ���������ݿ����";
		}
		else
		{
			cout << "Endpoint[" << _PlayerID << "]: �Ѳ����µ�ϵͳ����"<< endl;
		}
	}

	running = true;
	// ���ض˿ں�
	return _port;
}

void Endpoint::process()
{
	while (running)
	{
		/*
		* ������ĳ�Ա������Ϊthread�ĵ�һ������ʱ���ڶ���������Ҫ��һ����Ķ���
		* ��Ȼ�����Ī������Ĵ��󣺡�std::invoke��: δ�ҵ�ƥ������غ���
		* �������Ǵ���������this����
		*/
		thread listenThread(&Endpoint::listenFunc,this);
		listenThread.join();
	}
}


void Endpoint::listenFunc()
{
	while (running)
	{
		sockaddr_in clientAddr;
		int nSize = sizeof(clientAddr);
		clientSocket = accept(endpointSocket, (sockaddr*)&clientAddr, &nSize);
		if (clientSocket == INVALID_SOCKET)
		{
			if (running)
			{
				// �������running��˵������hub�����Ͽ�����
				cout << "��Client����ʧ�ܣ�\n";
			}
			closesocket(clientSocket);
			break;
		}
		cout << "Endpoint[" << _PlayerID << "]�ɹ���" << inet_ntoa(clientAddr.sin_addr) << "���û�����" << endl;
		
		while (running)
		{
			char recvbuf[DEFAULT_BUFLEN];
			int iResult;
			iResult = recv(clientSocket, recvbuf, DEFAULT_BUFLEN, 0);
			if (iResult > 0)
			{
				// �ɹ�����
				//recvbuf[iResult] = 0;
				cout <<"Endpoint[" << _PlayerID << "] received request:" << recvbuf << endl;
				dealClientInfo(recvbuf);
			}
			else if (iResult == 0)
			{
				//���ӶϿ�
				running = false;
				_online = false;
				cout << "Connection closing...\n";
			}
			else
			{
				running = false;
				_online = false;
				cout << "recv failed: " << WSAGetLastError() << endl;
				closesocket(clientSocket);
				WSACleanup();
				return;
			}
		}
		
	}
}

/* ָ��ģ��
 * <changePokemonName> <PlayerID> <pokemonid> <newname>
 * <getPokemonList> <userid>
 * <getUserList>
 * <logout>
 * <changePassword> <id> <oldpassword> <newpassword>
*/

void Endpoint::dealClientInfo(const char* recvbuf)
{
	auto strs = strfunc.split_str(recvbuf, ' ');
	if (strs[0]=="logout")
	{
		logOut();
	}
	else if (strs[0] == "changePokemonName")
	{
		int pokemonid = stoi(strs[1]);
		string newname = strs[2];
		changePokemonName(pokemonid,newname);
	}
	else if (strs[0] == "getPokemonList")
	{
		int userid = stoi(strs[1]);
		getPokemonList(userid);
	}
	else if (strs[0] == "getUserList")
	{
		getUserList();
	}
	else if (strs[0] == "changePassword")
	{
		string oldpassword = strs[2],newpassword = strs[3];
		changePassword(stoi(strs[1]), oldpassword,newpassword);
	}
	else if (strs[0] == "getPokemonInfo")
	{
		int pokemonID = stoi(strs[1]);
		getPokemonInfo(pokemonID);
	}
	else if (strs[0] == "battle")
	{
		int pokemonid1 = stoi(strs[1]), pokemonid2 = stoi(strs[2]);
		upgradeBattle(pokemonid1, pokemonid2);
	}
	else if (strs[0] == "changePokemonMaster")
	{
		int pokemonid = stoi(strs[1]), playerid = stoi(strs[2]);
		changePokemonMaster(pokemonid, playerid);
	}
	else if (strs[0] == "losePokemon")
	{
		losePokemon(_PlayerID);
	}
	else
	{
		string resStr = "recv INVALID requset!";
		cout << resStr << endl;
		buf2 = resStr;
	}
	// �����ظ�����
	if(buf2!="")
		send(clientSocket, buf2.c_str(), buf2.size(), 0);
	buf2 = "";

}

void Endpoint::logOut()
{
	//���ӶϿ�
	running = false;
	_online = false;

	//�޸����ݿ�online�ֶ�
	char *errMsg;
	string sql = "UPDATE Login SET online = 0 WHERE id = " + to_string(_PlayerID);
	if (sqlite3_exec(db, sql.c_str(), sqlite3_nonusecallback, NULL, &errMsg) != SQLITE_OK)
	{
		cout << "Endpoint[" << _PlayerID << "]: sqlite error:" << *errMsg << endl;
		sqlite3_free(errMsg);
		buf2 = "���������ݿ����";
		strcpy(buf, "���������ݿ����");
		return;
	}

	string logoutInfo = "Player " + to_string(_PlayerID) + " logout...";
	cout << logoutInfo << endl;
	cout << "Connection closing...\n";
	buf2 = "Accept.\n";
}

void Endpoint::changePassword(int PlayerID, const string oldpassword, const string newpassword)
{
	cout << "changePassword" << endl;

	//�Ȳ�ѯ�����룬������ȷ�򷵻�
	string sql = "SELECT password FROM Login WHERE id=" 
		+ to_string(PlayerID);
	char ** sqlResult;
	int nRow, nColumn;
	char* errMsg;
	if (sqlite3_get_table(db,sql.c_str(),&sqlResult,&nRow,&nColumn,&errMsg) != SQLITE_OK)
	{
		cout << "Endpoint[" << _PlayerID << "]: sqlite error:" << errMsg << endl;
		sqlite3_free(errMsg);
		//strcpy(buf, "���������ݿ����");
		buf2 = "���������ݿ����";
		return;
	}
	else
	{
		if (nRow == 0)
		{
			cout << "Endpoint[" << _PlayerID << "]: Invalid playerID" << errMsg << endl;
			//strcpy(buf, "��Ч�����ID");
			buf2 = "��Ч�����ID";
			return;
		}
		else
		{
			string user_password = sqlResult[1];
			if (user_password != oldpassword)
			{
				cout << "Endpoint[" << _PlayerID << "]: ԭ�������"<< endl;
				buf2 = "ԭ�������";
				//strcpy(buf, "ԭ�������");
				return;
			}
			else
			{
				// free
				sqlite3_free_table(sqlResult);
				// ִ���޸���������ݿ����
				sql = "UPDATE login SET password = '"+newpassword+"' WHERE id= "
					+ to_string(PlayerID);

				if (sqlite3_exec(db, sql.c_str(), sqlite3_nonusecallback, NULL, &errMsg) != SQLITE_OK)
				{
					cout << "Endpoint[" << _PlayerID << "]: sqlite error:" << *errMsg << endl;
					sqlite3_free(errMsg);
					buf2 = "���������ݿ����";
					//strcpy(buf, "���������ݿ����");
					return;
				}
				else
				{
					cout << "Accept.\n";
					buf2 = "Accept.\n";
					strcpy(buf, "Accept.\n");
					return;
				}
			}
		}
	}

}

void Endpoint::getPokemonList(int PlayerID)
{
	cout << "getPokemonList" << endl;

	string sql;
	char **sqlResult;
	int nRow, nColumn;
	char *errMsg;

	// ���ʤ��
	if (PlayerID != 8888 && PlayerID != 0)
	{
		sql = "SELECT win_round,total_round FROM Login WHERE id = " + to_string(PlayerID);
		if (sqlite3_get_table(db, sql.c_str(), &sqlResult, &nRow, &nColumn, &errMsg) != SQLITE_OK)
		{
			cout << "Endpoint[" << _PlayerID << "]: sqlite error:" << errMsg << endl;
			sqlite3_free(errMsg);
			buf2 = "���������ݿ����";
			strcpy(buf, "���������ݿ����");
			return;
		}
		else
		{
			if (nRow == 0)
			{
				cout << "Endpoint[" << _PlayerID << "]: invalid playerID:" << endl;
				buf2 = "��Ч��PlayerID";
				strcpy(buf, "��Ч��PlayerID");
				return;
			}
			else
			{
				
				buf2 = string(sqlResult[2])+" "+ string(sqlResult[3]) +"\n";
				sqlite3_free_table(sqlResult);
			}
		}
	}
	else
		buf2 = "\n";

	// ���С����
	// playerid = 0��������ϵͳ�ڲ�С����
	// playerid = 8888�������������Լ�������С����
	if(PlayerID!=8888)
		sql = "SELECT id,userid,name,race,lv FROM Pokemon WHERE userid = " + to_string(PlayerID);
	else
		sql = "SELECT id,userid,name,race,lv FROM Pokemon WHERE userid != " + to_string(_PlayerID);
	if (sqlite3_get_table(db, sql.c_str(), &sqlResult, &nRow, &nColumn, &errMsg) != SQLITE_OK)
	{
		cout << "Endpoint[" << _PlayerID << "]: sqlite error:" << errMsg << endl;
		sqlite3_free(errMsg);
		buf2 = "���������ݿ����";
		strcpy(buf, "���������ݿ����");
		return;
	}
	else
	{
		if (nRow == 0)
		{
			cout << "Endpoint[" << _PlayerID << "]: invalid playerID:" << endl;
			buf2 = "��Ч��PlayerID";
			strcpy(buf, "��Ч��PlayerID");
			return;
		}
		else
		{
			string result="";
			for (int i = 1; i <= nRow; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					result += sqlResult[5 * i + j];
					result += " ";
				}
				result += '\n';
			}
			buf2 += result;
			sqlite3_free_table(sqlResult);
		}
	}
	

}

void Endpoint::changePokemonName(int pokemonid, string newname)
{
	cout << "changePokemonName" << endl;

	string sql;
	char* errMsg;

	sql = "UPDATE Pokemon SET name = '"+newname+"' WHERE id= "+to_string(pokemonid);

	if (sqlite3_exec(db, sql.c_str(), sqlite3_nonusecallback, NULL, &errMsg) != SQLITE_OK)
	{
		cout << "Endpoint[" << _PlayerID << "]: sqlite error:" << *errMsg << endl;
		sqlite3_free(errMsg);
		buf2 = "���������ݿ����";
		strcpy(buf, "���������ݿ����");
		return;
	}
	else
	{
		cout << "Accept.\n";
		strcpy(buf, "Accept.\n");
		buf2 = "Accept.\n";
		return;
	}
}

void Endpoint::getUserList()
{
	cout << "getUserList" << endl;
	
	string sql;
	char **sqlResult;
	int nRow, nColumn;
	char *errMsg;
	
	sql = "SELECT id,username,online FROM Login";

	if (sqlite3_get_table(db, sql.c_str(), &sqlResult, &nRow, &nColumn, &errMsg) != SQLITE_OK)
	{
		cout << "Endpoint[" << _PlayerID << "]: sqlite error:" << errMsg << endl;
		sqlite3_free(errMsg);
		buf2 = "���������ݿ����";
		strcpy(buf, "���������ݿ����");
		return;
	}
	else
	{
		string result = "";
		for (int i = 1; i <= nRow; i++)
		{
			result += sqlResult[3 * i];
			result += " ";
			result += sqlResult[3 * i + 1];
			result += " ";
			result += sqlResult[3 * i + 2];
			result += "\n";
		}
		buf2 = result;
		cout << buf2;
		strcpy(buf, result.c_str());
		sqlite3_free_table(sqlResult);
	}
}

void Endpoint::getPokemonInfo(int PokemonID)
{
	cout << "getPokemonInfo" << endl;

	string sql;
	char **sqlResult;
	int nRow, nColumn;
	char *errMsg;

	sql = "SELECT name,race,atk,dfs,hp,speed,lv,ep,userid FROM Pokemon WHERE id = "+to_string(PokemonID);

	if (sqlite3_get_table(db, sql.c_str(), &sqlResult, &nRow, &nColumn, &errMsg) != SQLITE_OK)
	{
		cout << "Endpoint[" << _PlayerID << "]: sqlite error:" << errMsg << endl;
		sqlite3_free(errMsg);
		buf2 = "���������ݿ����";
		strcpy(buf, "���������ݿ����");
		return;
	}
	else
	{
		string result = "";
		for (int i = 1; i <= nRow; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				result += sqlResult[9 * i + j];
				result += " ";
			}
		}
		buf2 = result;
		cout << buf2;
		strcpy(buf, result.c_str());
		sqlite3_free_table(sqlResult);
	}
}

void Endpoint::savePokemonToDB(const Pokemon &pokemon)
{
	cout << "savePokemonToDB" << endl;
	// ���д���

	/*
	* SQLITE�е�REPLACE ���
	* replace����ɾ��ԭ�е�һ����¼�� ���Ҳ���һ���µļ�¼���滻ԭ��¼
	* replace����滻һ����¼�������У� �����replace�����û��ָ��ĳ�У� ��replace֮�����е�ֵ���ÿ�
	* replace��������ȷ�����滻������һ����¼
	* replace��䲻�ܸ���where�Ӿ�����λҪ���滻�ļ�¼
	* ���ִ��replace���ʱ�� ������Ҫ�滻�ļ�¼�� ��ô�ͻ����һ���µļ�¼��
	* ����²���Ļ��滻�ļ�¼�У� ���ֶκͱ��е�������¼��ͻ�� ��ô��ɾ������������¼��
	*/

	/*
	* SQLITE�е�UPDATE��䣨��Ҫ������REPLACE����
	* update���ʹ��where�Ӿ䶨λ�����µļ�¼��
	* update������һ�θ���һ����¼�� Ҳ���Ը��¶�����¼�� ֻҪ�������¼������where�Ӿ��Ҫ��
	* updateֻ����ԭ��¼�ϸ����ֶε�ֵ�� ����ɾ��ԭ�м�¼�� Ȼ���ٲ����¼�¼��
	* �����update�����û��ָ��һЩ�ֶΣ� ��ô��Щ�ֶ�ά��ԭ�е�ֵ�� �����ᱻ�ÿգ�
	*/

	char* errMsg;

	string sql = "UPDATE Pokemon SET ";
	sql += "atk = " + to_string(pokemon.atk())+",";
	sql += "dfs = " +to_string(pokemon.dfs()) + ",";
	sql += "hp = " +to_string(pokemon.hp()) + ",";
	sql += "speed = " + to_string(pokemon.speed()) + ",";
	sql += "lv = " + to_string(pokemon.lv()) + ",";
	sql += "ep = " + to_string(pokemon.ep()) + " ";
	sql += "WHERE id = " + to_string(pokemon.pokemonid());

	if (sqlite3_exec(db, sql.c_str(), sqlite3_nonusecallback, NULL, &errMsg)!=SQLITE_OK)
	{
		cout << "Endpoint[" << _PlayerID << "]: sqlite error:" << errMsg << endl;
		sqlite3_free(errMsg);
		buf2 = "���������ݿ����";
		return;
	}
	else
	{
		cout << "Save Pokemon"<<pokemon.pokemonid()<<" to database successfully" << endl;
		return;
	}
}

void Endpoint::upgradeBattle(int pokemonid_1, int pokemonid_2)
{
	cout << "upgradeBattle: pokemon"<<pokemonid_1<<" vs pokemon"<<pokemonid_2 << endl;
	int raceIdx, atk, dfs, hp, speed, lv, ep;
	string name;
	string sql;
	char **sqlResult;
	int nRow, nColumn;
	char *errMsg;

	sql = "SELECT name,race,atk,dfs,hp,speed,lv,ep FROM Pokemon WHERE id = " + to_string(pokemonid_1);

	if (sqlite3_get_table(db, sql.c_str(), &sqlResult, &nRow, &nColumn, &errMsg) != SQLITE_OK)
	{
		cout << "Endpoint[" << _PlayerID << "]: sqlite error:" << errMsg << endl;
		sqlite3_free(errMsg);
		buf2 = "���������ݿ����";
		strcpy(buf, "���������ݿ����");
		return;
	}
	else
	{
		raceIdx = atoi(sqlResult[9]);
		name = sqlResult[8];
		atk = atoi(sqlResult[10]), dfs = atoi(sqlResult[11]), hp = atoi(sqlResult[12]),
			speed = atoi(sqlResult[13]), lv = atoi(sqlResult[14]), ep = atoi(sqlResult[15]);
		sqlite3_free_table(sqlResult);
	}
	Pokemon p1(pokemonid_1,raceIdx, name, atk, dfs, hp, speed, lv, ep);

	sql = "SELECT name,race,atk,dfs,hp,speed,lv,ep FROM Pokemon WHERE id = " + to_string(pokemonid_2);

	if (sqlite3_get_table(db, sql.c_str(), &sqlResult, &nRow, &nColumn, &errMsg) != SQLITE_OK)
	{
		cout << "Endpoint[" << _PlayerID << "]: sqlite error:" << errMsg << endl;
		sqlite3_free(errMsg);
		buf2 = "���������ݿ����";
		strcpy(buf, "���������ݿ����");
		return;
	}
	else
	{
		raceIdx = atoi(sqlResult[9]);
		name = sqlResult[8];
		atk = atoi(sqlResult[10]), dfs = atoi(sqlResult[11]), hp = atoi(sqlResult[12]),
			speed = atoi(sqlResult[13]), lv = atoi(sqlResult[14]), ep = atoi(sqlResult[15]);
		sqlite3_free_table(sqlResult);
	}
	Pokemon p2(pokemonid_2,raceIdx, name, atk, dfs, hp, speed, lv, ep);

	BattleController battle(p1, p2,clientSocket, AUTOFIGHT);
	int winner = battle.startBattleForClient();
	if (winner == 0)
	{
		cout << "Endpoint[" << _PlayerID << "]: battle error" << endl;
		return;
	}

	//��С����洢�����ݿ�
	savePokemonToDB(p1);
	//savePokemonToDB(p2);

	//�洢��ս���
	total_round++;
	//��һ�ʤ
	if (winner == 1)
	{
		win_round++;
	}

	//����database
	sql = "UPDATE Login SET win_round = " + to_string(win_round) + ", total_round = " + to_string(total_round)+" WHERE id = "+to_string(_PlayerID);
	if (sqlite3_exec(db, sql.c_str(), sqlite3_nonusecallback, NULL, &errMsg) != SQLITE_OK)
	{
		cout << "Endpoint[" << _PlayerID << "]: sqlite error:" << *errMsg << endl;
		sqlite3_free(errMsg);
		buf2 = "���������ݿ����";
		return;
	}
	cout << "Endpoint[" << _PlayerID << "]: ʤ���Ѹ��£�win_round/total_round��"<<win_round<<"/"<<total_round << endl;
}

void Endpoint::changePokemonMaster(int pokemonid, int playerid)
{
	cout << "changePokemonMaster" << endl;

	string sql;
	char* errMsg;

	sql = "UPDATE Pokemon SET userid = " + to_string(playerid) + " WHERE id= " + to_string(pokemonid);

	if (sqlite3_exec(db, sql.c_str(), sqlite3_nonusecallback, NULL, &errMsg) != SQLITE_OK)
	{
		cout << "Endpoint[" << _PlayerID << "]: sqlite error:" << *errMsg << endl;
		sqlite3_free(errMsg);
		buf2 = "���������ݿ����";
		return;
	}
	else
	{
		cout << "Accept.\n";
		return;
	}
}

void Endpoint::losePokemon(int playerid)
{
	cout <<playerid<< "lose a pokemon" << endl;

	string sql;
	char **sqlResult;
	int nRow, nColumn;
	char *errMsg;

	sql = "SELECT id FROM Pokemon WHERE userid = " + to_string(playerid);
	if (sqlite3_get_table(db, sql.c_str(), &sqlResult, &nRow, &nColumn, &errMsg) != SQLITE_OK)
	{
		cout << "Endpoint[" << _PlayerID << "]: sqlite error:" << errMsg << endl;
		sqlite3_free(errMsg);
		buf2 = "���������ݿ����";
		return;
	}
	else
	{
		if (nRow == 0)
		{
			cout << "Endpoint[" << _PlayerID << "]: invalid playerID:" << endl;
			buf2 = "��Ч��PlayerID";
			strcpy(buf, "��Ч��PlayerID");
			return;
		}
		else
		{
			vector<int> pokemons;
			for (int i = 1; i <= nRow; i++)
			{
				pokemons.push_back(atoi(sqlResult[i]));
			}
			sqlite3_free_table(sqlResult);

			int size = pokemons.size();
			//����С����
			bool give_back = size == 1 ? true : false;
			//ѡ����С��������
			int pick_num = size >= 3 ? 3 : size;
			vector<int> pick_pokemon;

			srand((unsigned)time(NULL));
			for (; pick_num>0;)
			{
				int rand_num = rand() % size;
				if (pokemons[rand_num]>0)
				{
					pick_pokemon.push_back(pokemons[rand_num]);
					pokemons[rand_num] = -1;
					pick_num--;
				}
			}

			//ѡ��Ҫ��������С����

			sql = "SELECT id,name,race,atk,dfs,hp,speed,lv FROM Pokemon WHERE ";
			sql += "id = " + to_string(pick_pokemon[0]);
			if (pick_pokemon.size() > 1)
				sql += " OR id = " + to_string(pick_pokemon[1]);
			if (pick_pokemon.size() > 2)
				sql += " OR id = " + to_string(pick_pokemon[2]);

			if (sqlite3_get_table(db, sql.c_str(), &sqlResult, &nRow, &nColumn, &errMsg) != SQLITE_OK)
			{
				cout << "Endpoint[" << _PlayerID << "]: sqlite error:" << errMsg << endl;
				sqlite3_free(errMsg);
				buf2 = "���������ݿ����";
				strcpy(buf, "���������ݿ����");
				return;
			}
			else
			{
				string result = "";
				for (int i = 1; i <= nRow; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						result += sqlResult[8 * i + j];
						result += " ";
					}
					result += '\n';
				}
				buf2 = result;
				cout << buf2;
				sqlite3_free_table(sqlResult);
			}

			if (give_back)
			{
				int rand_race = rand() % RACE_NUM;
				Pokemon p(rand_race,"");
				sql = "INSERT INTO Pokemon (userid,name,race,atk,dfs,hp,speed,lv,ep)";
				sql += " VALUES ('" + to_string(playerid) + "', '" + p.name();
				sql += "', " + to_string(rand_race) + ", " + to_string(p.atk());
				sql += ", " + to_string(p.dfs()) + ", " + to_string(p.hp());
				sql += ", " + to_string(p.speed()) + ", " + to_string(1);
				sql += ", " + to_string(0) + "); ";
				if (sqlite3_exec(db, sql.c_str(), sqlite3_nonusecallback, NULL, &errMsg) != SQLITE_OK)
				{
					cout << "Endpoint[" << _PlayerID << "]: sqlite error:" << errMsg << endl;
					sqlite3_free(errMsg);
					strcpy(buf, "���������ݿ����");
					return;
				}
			}

		}
	}
}