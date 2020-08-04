#include "server.h"

void Hub::run()
{
#pragma region init database
	cout << "Hub: Init database...\n";
	if (sqlite3_open("server.db", &db))
	{
		cout << "Hub: Can NOT open database: " << sqlite3_errmsg(db) << endl;
		return;
	}
	// create tables whether they are already exist or not
	char *errMsg;
	string sql = "create table if not exists Login(";
	sql += "id integer primary key,";
	sql += "username text unique not null,";
	sql += "password text not null,";
	sql += "online integer not null,";
	sql += "win_round integer not null,";
	sql += "total_round integer not null";
	sql += ");";
	if (sqlite3_exec(db, sql.c_str(), sqlite3_nonusecallback, NULL, &errMsg) != SQLITE_OK)
	{
		cout << "Hub: Sqlite3 error: " << errMsg << endl;
		sqlite3_free(errMsg);
	}
	sql = "create table if not exists Pokemon(";
	sql += "id integer primary key,";
	sql += "userid integer not null,";
	sql += "name text not null,";
	sql += "race int not null,";
	sql += "atk int not null,";
	sql += "dfs int not null,";
	sql += "hp int not null,";
	sql += "speed int not null,";
	sql += "lv int not null,";
	sql += "ep int not null";
	sql += ");";
	if (sqlite3_exec(db, sql.c_str(), sqlite3_nonusecallback, NULL, &errMsg) != SQLITE_OK)
	{
		cout << "Hub: Sqlite3 error: " << errMsg << endl;
		sqlite3_free(errMsg);
	}
	cout << "Done.\n";
#pragma endregion

#pragma region init sock
	// 初始化 Winsock
	WSADATA wsaData;
	// 调用WSAStartup以启动WS2_32.dll的使用
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult!=0)
	{
		cout << "WSAStartup failed: " << iResult << endl;
		return;
	}

	hubSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in hubAddr;
	hubAddr.sin_family = PF_INET;
	hubAddr.sin_port = htons(HUB_PORT);
	hubAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	
	cout << "Hub:Socket binding..." << endl;

	// 将创建的套接字与IP地址、接口绑定
	if (::bind(hubSocket, (sockaddr*)&hubAddr, sizeof(hubAddr))==SOCKET_ERROR)
	{
		cout << "bind failed with error: " << WSAGetLastError() << endl;
		closesocket(hubSocket);
		WSACleanup();
		return;
	}
	cout << "Done.\n";
	cout << "Hub:Socket listening..." << endl;
	// 监听套接字
	if (listen(hubSocket, SOMAXCONN) == SOCKET_ERROR) {
		cout << "listen failed with error: " << WSAGetLastError() << endl;
		closesocket(hubSocket);
		WSACleanup();
		return ;
	}
	cout << "Done.\n";
	cout << "Hub is running at port "<<HUB_PORT<<".\n";

#pragma endregion

	running = true;
	thread listenThread(&Hub::ListenFunc, this);
	//thread terminateThread(&Hub::TerminateFunc, this);
	// 执行完这两个线程再执行后续过程
	listenThread.join();
	//terminateThread.join();

	// Hub结束
	WSACleanup();
	sqlite3_close(db);
}

void Hub::ListenFunc()
{
	while(running)
	{
		// 与client建立连接
		sockaddr_in addrClient = {};
		int nSize = sizeof(addrClient);
		clientSocket = accept(hubSocket, (sockaddr*)&addrClient, &nSize);
		if (clientSocket == INVALID_SOCKET)
		{
			if (running)
			{
				// 如果还在running，说明并非hub主动断开连接
				cout << "与Client连接失败！\n";
			}
			closesocket(clientSocket);
			break;
		}

		// 连接成功
		cout << "Hub成功与" << inet_ntoa(addrClient.sin_addr) << "连接!\n";

		while (running)
		{
			// 处理客户端发送的数据
		// 目前只有登录、注册请求
			char recvbuf[DEFAULT_BUFLEN];
			int iResult;

			// 监听来自client的信息
			/*
			* 返回说明： 
			* 成功执行时，返回接收到的字节数。
			* 另一端已关闭则返回0。
			* 失败返回-1
			*/
			iResult = recv(clientSocket, recvbuf, DEFAULT_BUFLEN, 0);
			if (iResult > 0) {
				// 成功接收
				//recvbuf[iResult] = 0;
				cout << "Hub received request:" << recvbuf << endl;
				dealClientInfo(recvbuf);
			}
			else if (iResult == 0)
			{
				cout << "Connection closing...\n";
				break;
			}
			else {
				cout << "recv failed: " << WSAGetLastError() << endl;
				closesocket(clientSocket);
				break;
			}
			send(clientSocket, buf, DEFAULT_BUFLEN, 0);
		}
	}
}

//void Hub::TerminateFunc()
//{
//	_getch();
//	running = false;
//	closesocket(hubSocket);
//}

void Hub::dealClientInfo(const string &recv)
{
	auto strs=strfunc.split_str(recv, ' ');
	if (strs.size() < 2)
	{
		cout << "无效请求!" << endl;
		return;
	}
	else if (strs.size() == 3)
	{
		char *errMsg;
		cout << "收到Client请求如下:\n";

		/*************处理登录**************/
		if (strs[0] == "login")
		{
			cout << "请求类型: " << strs[0];
			cout << "\t用户名: " << strs[1];
			cout << "\t密码: " << strs[2]<<endl;
			string username = strs[1];
			string password = strs[2];
			string sql = "SELECT id FROM Login WHERE username = '"+strs[1]+"' AND password = '"+strs[2]+"'";
			char **sqlResult;
			int nRow, nColumn;
			if (sqlite3_get_table(db,sql.c_str(),&sqlResult,&nRow,&nColumn,&errMsg)!=SQLITE_OK)
			{
				cout << "Hub: Sqlite3 error: " << errMsg << endl;
				sqlite3_free(errMsg);
				strcpy(buf, "服务器数据库错误");
				return;
			}
			else
			{
				if (nRow == 0)
				{
					// username and password mismatch
					cout << "Hub: Login error : Invalid username:" << username << " or password:" << password << endl;
					strcpy(buf, "用户名或密码错误");
					return;
				}
				else
				{
					// login successfully
					// sqlResult[0]="id",sqlResult[1]="   玩家id    "
					int id = atoi(sqlResult[1]);

					// 判断用户是否已经登录
					bool userExist = false;

					for (auto endpoint : endpoints)
					{
						// 该用户存在
						if (id == endpoint->getPlayerID())
						{

							userExist = true;
							// 且在线
							if (endpoint->getOnline())
							{
								strcpy(buf, "用户已经在线，请勿重复登录!");
								return;
							}
							// 这个else目前来说没有用，因为用户掉线endpoint就回收了
							else
							{
								// 不在线了
								// strcpy(buf, to_string(endpoint->getPort()).c_str());
							}
							break;
						}
					}

					// 为用户分配Endpoint
					auto endpoint=new Endpoint	(id,db,*this);
					int endpointPort = endpoint->start();
					if (endpointPort == 0)
					{
						// 成功了port不为是0
						cout << "Endpoint[" << id << "]:Init failed..." << endl;
						strcpy(buf, "服务器错误，注册失败！");
						return;
					}

					//修改数据库online字段
					char *errMsg;
					string sql = "UPDATE Login SET online = 1 WHERE id = " + to_string(id);
					if (sqlite3_exec(db, sql.c_str(), sqlite3_nonusecallback, NULL, &errMsg) != SQLITE_OK)
					{
						cout << "Endpoint[" << id << "]: sqlite error:" << *errMsg << endl;
						sqlite3_free(errMsg);
						//buf2 = "服务器数据库错误";
						strcpy(buf, "服务器数据库错误");
						return;
					}

					// 获取该用户的胜局和总局数
					/*char** sqlResult;
					int nRow, nColumn;
					char* errMsg;*/
					sql = "SELECT win_round, total_round FROM Login WHERE id = " + to_string(id);
					if (sqlite3_get_table(db, sql.c_str(),&sqlResult,&nRow,&nColumn,&errMsg) != SQLITE_OK)
					{
						cout << "Endpoint[" << id << "]: sqlite error:" << *errMsg << endl;
						sqlite3_free(errMsg);
						strcpy(buf, "服务器数据库错误");
						return;
					}
					endpoint->setWinRound(atoi(sqlResult[2]));
					endpoint->setTotalRound(atoi(sqlResult[3]));

					// 在不同线程中操作了endpoints，因此加个锁
					hub_mute.lock();
					endpoints.push_back(endpoint);
					hub_mute.unlock();

					// 另开一个线程管理endpoint
					thread endpointHandlerThread(&Hub::endpointHandler,this,endpoint);
					// Hub中止了Endpoint不必中止
					endpointHandlerThread.detach();
					
					// 返回格式 <port> <id>
					string sendbuf = to_string(endpointPort) + " " + to_string(id) + " " + to_string(endpoint->getWinRound()) + " " + to_string(endpoint->getTotalRound());
					strcpy(buf, sendbuf.c_str());
					cout << username << "登录成功，端口号为:" << sendbuf << endl;

				}
			}

		}
		/*************处理注册**************/
		else if (strs[0] == "logon")
		{
			cout << "请求类型: " << strs[0];
			cout << "\t用户名: " << strs[1];
			cout << "\t密码: " << strs[2]<<endl;
			//处理函数
			string username = strs[1];
			string password = strs[2];
			
			// 直接插入数据库，看是否重复
			string sql = "INSERT INTO Login (username, password, online, win_round, total_round) VALUES ('" + username + "', '" + password + "', " + 
				to_string(0)+", "+ to_string(0)+", " + to_string(0)+");";
			if (sqlite3_exec(db, sql.c_str(), sqlite3_nonusecallback, NULL, &errMsg) != SQLITE_OK)
			{
				if (strcmp(errMsg, "UNIQUE constraint failed: Login.username") == 0)
				{
					cout << "Hub: Sqlite3 error: 用户名" << username << "重复" << endl;
					sqlite3_free(errMsg);
					strcpy(buf, "用户名已被占用，请修改用户名!");
					return;
				}
				cout << "Hub: Sqlite3 error: " << errMsg << endl;
				sqlite3_free(errMsg);
				strcpy(buf, "服务器数据库错误");
				return;
			}

			// 获得刚插入的用户的id
			sql = "SELECT id FROM Login WHERE username = '" + strs[1] + "' AND password = '" + strs[2] + "'";
			char **sqlResult;
			int nRow, nColumn;
			if (sqlite3_get_table(db, sql.c_str(), &sqlResult, &nRow, &nColumn, &errMsg) != SQLITE_OK)
			{
				cout << "Hub: Sqlite3 error: " << errMsg << endl;
				sqlite3_free(errMsg);
				strcpy(buf, "服务器数据库错误");
				return;
			}

			// 随机给三个小精灵
			srand((unsigned)time(NULL));
			for (int i = 0; i < 3; i++)
			{
				// 获得该用户id
				int id = atoi(sqlResult[1]);
				int rand_race = rand() % RACE_NUM;
				Pokemon p(rand_race, "");
				sql = "INSERT INTO Pokemon (userid,name,race,atk,dfs,hp,speed,lv,ep)";
				sql += " VALUES ('" + to_string(id) + "', '" + p.name();
				sql += "', " + to_string(rand_race) + ", " + to_string(p.atk());
				sql += ", " + to_string(p.dfs()) + ", " + to_string(p.hp());
				sql += ", " + to_string(p.speed()) + ", " + to_string(1);
				sql += ", " + to_string(0) + "); ";
				if (sqlite3_exec(db, sql.c_str(), sqlite3_nonusecallback, NULL, &errMsg) != SQLITE_OK)
				{
					cout << "Hub: Sqlite3 error: " << errMsg << endl;
					sqlite3_free(errMsg);
					strcpy(buf, "服务器数据库错误");
					return;
				}

			}
			cout << username << "注册成功！" << endl;
			strcpy(buf, "Accept!\n");
		}
		else
		{
			strcpy(buf, "无效请求!");
			cout << "无效请求" << endl;
		}
	}
}

// 管理每一个endpoint
void Hub::endpointHandler(Endpoint *const endpoint)
{
	// endpoint仍在执行
	endpoint->process();

	// 中途退出，无法修改online状态
	// 修改数据库online字段
	int _PlayerID = endpoint->getPlayerID();
	char *errMsg;
	string sql = "UPDATE Login SET online = 0 WHERE id = " + to_string(_PlayerID);
	if (sqlite3_exec(db, sql.c_str(), sqlite3_nonusecallback, NULL, &errMsg) != SQLITE_OK)
	{
		cout << "Endpoint[" << _PlayerID << "]: sqlite error:" << *errMsg << endl;
		sqlite3_free(errMsg);
		//buf2 = "服务器数据库错误";
		strcpy(buf, "服务器数据库错误");
		return;
	}

	// endpoint退出
	lock_guard<mutex> endpointsGuard(hub_mute);
	int eSize = endpoints.size();
	for (int i = 0; i < eSize; i++)
	{
		if (endpoints[i] == endpoint)
		{
			endpoints.erase(endpoints.begin()+i);
			delete endpoint;
			break;
		}
	}
}