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
	// 从数据库获取用户名
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
	// 初始化Wincock
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		cout << "WSAStartup failed: " << iResult << endl;
		return 0;
	}
	endpointSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	/**
	 * 随机获取端口号的方法
	 * 在bind之前将socket地址的sin_port设置为0，代表让系统分配端口
	 * 但是connect之后不能直接用sin_port来获取端口号
	 * 必须通过getsockname()获得当前已经被系统bind了的端口号的地址
	*/

	sockaddr_in endpointAddr;
	endpointAddr.sin_family = PF_INET;
	// 分配端口的任务交给OS
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
	
	// 现在使用getsockname()来得到端口号
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

	// 每次开启一个Endpoint产生一个新的Pokemon
	// 数量控制在20个以内
	// 查询有多少个系统精灵
	sql = "SELECT id FROM Pokemon WHERE userid = 0";
	if (sqlite3_get_table(db, sql.c_str(), &sqlResult,&nRow,&nColumn, &errMsg) != SQLITE_OK)
	{
		cout << "Endpoint[" << _PlayerID << "]: sqlite error:" << errMsg << endl;
		sqlite3_free(errMsg);
		//buf2 = "产生系统精灵时服务器数据库错误";
	}
	if (nRow < 20)
		generate_new_pokemon = true;
	else
		generate_new_pokemon = false;
	if (generate_new_pokemon)
	{
		// 获得该用户id
		int id = _PlayerID;
		int rand_race = rand() % RACE_NUM;
		Pokemon p(rand_race, "");
		// 随机给一个ep
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
			//buf2 =  "产生系统精灵时服务器数据库错误";
		}
		else
		{
			cout << "Endpoint[" << _PlayerID << "]:Initalization done."<< endl;
		}
	}
		
	running = true;
	// 返回端口号
	return _port;
}

void Endpoint::process()
{
	while (running)
	{
		/*
		* 当用类的成员函数作为thread的第一个参数时，第二个参数需要传一个类的对象！
		* 不然会出现莫名其妙的错误：“std::invoke”: 未找到匹配的重载函数
		* 常见的是传本身，比如this！！
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
				// 如果还在running，说明并非hub主动断开连接
				cout << "connect failed with client!\n";
			}
			closesocket(clientSocket);
			break;
		}
		cout << "Endpoint[" << _PlayerID << "]:connect to" << inet_ntoa(clientAddr.sin_addr) << "'s user successfully" << endl;
		
		while (running)
		{
			char recvbuf[DEFAULT_BUFLEN];
			int iResult;
			iResult = recv(clientSocket, recvbuf, DEFAULT_BUFLEN, 0);
			if (iResult > 0)
			{
				// 成功接收
				//recvbuf[iResult] = 0;
				cout <<"Endpoint[" << _PlayerID << "] received request:" << recvbuf << endl;
				dealClientInfo(recvbuf);
			}
			else if (iResult == 0)
			{
				//连接断开
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

/* 指令模板
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
	// 避免重复发送
	if(buf2!="")
		send(clientSocket, buf2.c_str(), buf2.size(), 0);
	buf2 = "";

}

void Endpoint::logOut()
{
	//连接断开
	running = false;
	_online = false;

	//修改数据库online字段
	char *errMsg;
	string sql = "UPDATE Login SET online = 0 WHERE id = " + to_string(_PlayerID);
	if (sqlite3_exec(db, sql.c_str(), sqlite3_nonusecallback, NULL, &errMsg) != SQLITE_OK)
	{
		cout << "Endpoint[" << _PlayerID << "]: sqlite error:" << *errMsg << endl;
		sqlite3_free(errMsg);
		buf2 = "服务器数据库错误";
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

	//先查询旧密码，若不正确则返回
	string sql = "SELECT password FROM Login WHERE id="
		+ to_string(PlayerID);
	char ** sqlResult;
	int nRow, nColumn;
	char* errMsg;
	if (sqlite3_get_table(db,sql.c_str(),&sqlResult,&nRow,&nColumn,&errMsg) != SQLITE_OK)
	{
		cout << "Endpoint[" << _PlayerID << "]: sqlite error:" << errMsg << endl;
		sqlite3_free(errMsg);
		buf2 = "服务器数据库错误";
		return;
	}
	else
	{
		if (nRow == 0)
		{
			cout << "Endpoint[" << _PlayerID << "]: Invalid playerID" << errMsg << endl;
			buf2 = "无效的玩家ID";
			return;
		}
		else
		{
			string user_password = sqlResult[1];
			if (user_password != oldpassword)
			{
				cout << "Endpoint[" << _PlayerID << "]：原密码错误" << endl;
				buf2 = "Wrong original password";
				return;
			}
			else
			{
				// free
				sqlite3_free_table(sqlResult);
				// 执行修改密码的数据库操作
				sql = "UPDATE login SET password = '"+newpassword+"' WHERE id= "
					+ to_string(PlayerID);

				if (sqlite3_exec(db, sql.c_str(), sqlite3_nonusecallback, NULL, &errMsg) != SQLITE_OK)
				{
					cout << "Endpoint[" << _PlayerID << "]: sqlite error:" << *errMsg << endl;
					sqlite3_free(errMsg);
					buf2 = "服务器数据库错误";
					return;
				}
				else
				{
					cout << "Accept.\n";
					buf2 = "Accept.\n";
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

	// 获得胜率
	if (PlayerID != 8888 && PlayerID != 0)
	{
		sql = "SELECT win_round,total_round FROM Login WHERE id = " + to_string(PlayerID);
		if (sqlite3_get_table(db, sql.c_str(), &sqlResult, &nRow, &nColumn, &errMsg) != SQLITE_OK)
		{
			cout << "Endpoint[" << _PlayerID << "]: sqlite error:" << errMsg << endl;
			sqlite3_free(errMsg);
			buf2 = "服务器数据库错误";
			return;
		}
		else
		{
			if (nRow == 0)
			{
				cout << "Endpoint[" << _PlayerID << "]: invalid playerID:" << endl;
				buf2 = "无效的PlayerID";
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

	// 获得小精灵
	// playerid = 0————系统内部小精灵
	// playerid = 8888————除了自己的所有小精灵
	if(PlayerID!=8888)
		sql = "SELECT id,userid,name,race,lv FROM Pokemon WHERE userid = " + to_string(PlayerID);
	else
		sql = "SELECT id,userid,name,race,lv FROM Pokemon WHERE userid != " + to_string(_PlayerID);
	if (sqlite3_get_table(db, sql.c_str(), &sqlResult, &nRow, &nColumn, &errMsg) != SQLITE_OK)
	{
		cout << "Endpoint[" << _PlayerID << "]: sqlite error:" << errMsg << endl;
		sqlite3_free(errMsg);
		buf2 = "服务器数据库错误";
		return;
	}
	else
	{
		if (nRow == 0)
		{
			cout << "Endpoint[" << _PlayerID << "]: invalid playerID:" << endl;
			buf2 = "无效的PlayerID";
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
		buf2 = "服务器数据库错误";
		return;
	}
	else
	{
		cout << "Accept.\n";
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
		buf2 = "服务器数据库错误";
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
		buf2 = "服务器数据库错误";
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
		sqlite3_free_table(sqlResult);
	}
}

void Endpoint::savePokemonToDB(const Pokemon &pokemon)
{
	cout << "savePokemonToDB" << endl;
	// 查有此人

	/*
	* SQLITE中的REPLACE 语句
	* replace语句会删除原有的一条记录， 并且插入一条新的记录来替换原记录
	* replace语句替换一条记录的所有列， 如果在replace语句中没有指定某列， 在replace之后这列的值被置空
	* replace根据主键确定被替换的是哪一条记录
	* replace语句不能根据where子句来定位要被替换的记录
	* 如果执行replace语句时， 不存在要替换的记录， 那么就会插入一条新的记录。
	* 如果新插入的或替换的记录中， 有字段和表中的其他记录冲突， 那么会删除那条其他记录。
	*/

	/*
	* SQLITE中的UPDATE语句（主要分析与REPLACE区别）
	* update语句使用where子句定位被更新的记录；
	* update语句可以一次更新一条记录， 也可以更新多条记录， 只要这多条记录都复合where子句的要求；
	* update只会在原记录上更新字段的值， 不会删除原有记录， 然后再插入新纪录；
	* 如果在update语句中没有指定一些字段， 那么这些字段维持原有的值， 而不会被置空；
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
		buf2 = "服务器数据库错误";
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
		buf2 = "服务器数据库错误";
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
		buf2 = "服务器数据库错误";
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

	//把小精灵存储到数据库
	savePokemonToDB(p1);

	//存储对战结果
	total_round++;
	//玩家获胜
	if (winner == 1)
	{
		win_round++;
	}

	//更新database
	sql = "UPDATE Login SET win_round = " + to_string(win_round) + ", total_round = " + to_string(total_round)+" WHERE id = "+to_string(_PlayerID);
	if (sqlite3_exec(db, sql.c_str(), sqlite3_nonusecallback, NULL, &errMsg) != SQLITE_OK)
	{
		cout << "Endpoint[" << _PlayerID << "]: sqlite error:" << *errMsg << endl;
		sqlite3_free(errMsg);
		buf2 = "服务器数据库错误";
		return;
	}
	cout << "Endpoint[" << _PlayerID << "]:win_round/total_round updated:"<<win_round<<"/"<<total_round << endl;
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
		buf2 = "服务器数据库错误";
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
		buf2 = "服务器数据库错误";
		return;
	}
	else
	{
		if (nRow == 0)
		{
			cout << "Endpoint[" << _PlayerID << "]: invalid playerID:" << endl;
			buf2 = "无效的PlayerID";
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
			//给回小精灵
			bool give_back = size == 1 ? true : false;
			//选出的小精灵数量
			int pick_num = size >= 3 ? 3 : size;
			vector<int> pick_pokemon;

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

			//选出要被抛弃的小精灵

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
				buf2 = "服务器数据库错误";
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
					return;
				}
			}

		}
	}
}