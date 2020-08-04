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
	// ��ʼ�� Winsock
	WSADATA wsaData;
	// ����WSAStartup������WS2_32.dll��ʹ��
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

	// ���������׽�����IP��ַ���ӿڰ�
	if (::bind(hubSocket, (sockaddr*)&hubAddr, sizeof(hubAddr))==SOCKET_ERROR)
	{
		cout << "bind failed with error: " << WSAGetLastError() << endl;
		closesocket(hubSocket);
		WSACleanup();
		return;
	}
	cout << "Done.\n";
	cout << "Hub:Socket listening..." << endl;
	// �����׽���
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
	// ִ�����������߳���ִ�к�������
	listenThread.join();
	//terminateThread.join();

	// Hub����
	WSACleanup();
	sqlite3_close(db);
}

void Hub::ListenFunc()
{
	while(running)
	{
		// ��client��������
		sockaddr_in addrClient = {};
		int nSize = sizeof(addrClient);
		clientSocket = accept(hubSocket, (sockaddr*)&addrClient, &nSize);
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

		// ���ӳɹ�
		cout << "Hub�ɹ���" << inet_ntoa(addrClient.sin_addr) << "����!\n";

		while (running)
		{
			// ����ͻ��˷��͵�����
		// Ŀǰֻ�е�¼��ע������
			char recvbuf[DEFAULT_BUFLEN];
			int iResult;

			// ��������client����Ϣ
			/*
			* ����˵���� 
			* �ɹ�ִ��ʱ�����ؽ��յ����ֽ�����
			* ��һ���ѹر��򷵻�0��
			* ʧ�ܷ���-1
			*/
			iResult = recv(clientSocket, recvbuf, DEFAULT_BUFLEN, 0);
			if (iResult > 0) {
				// �ɹ�����
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
		cout << "��Ч����!" << endl;
		return;
	}
	else if (strs.size() == 3)
	{
		char *errMsg;
		cout << "�յ�Client��������:\n";

		/*************�����¼**************/
		if (strs[0] == "login")
		{
			cout << "��������: " << strs[0];
			cout << "\t�û���: " << strs[1];
			cout << "\t����: " << strs[2]<<endl;
			string username = strs[1];
			string password = strs[2];
			string sql = "SELECT id FROM Login WHERE username = '"+strs[1]+"' AND password = '"+strs[2]+"'";
			char **sqlResult;
			int nRow, nColumn;
			if (sqlite3_get_table(db,sql.c_str(),&sqlResult,&nRow,&nColumn,&errMsg)!=SQLITE_OK)
			{
				cout << "Hub: Sqlite3 error: " << errMsg << endl;
				sqlite3_free(errMsg);
				strcpy(buf, "���������ݿ����");
				return;
			}
			else
			{
				if (nRow == 0)
				{
					// username and password mismatch
					cout << "Hub: Login error : Invalid username:" << username << " or password:" << password << endl;
					strcpy(buf, "�û������������");
					return;
				}
				else
				{
					// login successfully
					// sqlResult[0]="id",sqlResult[1]="   ���id    "
					int id = atoi(sqlResult[1]);

					// �ж��û��Ƿ��Ѿ���¼
					bool userExist = false;

					for (auto endpoint : endpoints)
					{
						// ���û�����
						if (id == endpoint->getPlayerID())
						{

							userExist = true;
							// ������
							if (endpoint->getOnline())
							{
								strcpy(buf, "�û��Ѿ����ߣ������ظ���¼!");
								return;
							}
							// ���elseĿǰ��˵û���ã���Ϊ�û�����endpoint�ͻ�����
							else
							{
								// ��������
								// strcpy(buf, to_string(endpoint->getPort()).c_str());
							}
							break;
						}
					}

					// Ϊ�û�����Endpoint
					auto endpoint=new Endpoint	(id,db,*this);
					int endpointPort = endpoint->start();
					if (endpointPort == 0)
					{
						// �ɹ���port��Ϊ��0
						cout << "Endpoint[" << id << "]:Init failed..." << endl;
						strcpy(buf, "����������ע��ʧ�ܣ�");
						return;
					}

					//�޸����ݿ�online�ֶ�
					char *errMsg;
					string sql = "UPDATE Login SET online = 1 WHERE id = " + to_string(id);
					if (sqlite3_exec(db, sql.c_str(), sqlite3_nonusecallback, NULL, &errMsg) != SQLITE_OK)
					{
						cout << "Endpoint[" << id << "]: sqlite error:" << *errMsg << endl;
						sqlite3_free(errMsg);
						//buf2 = "���������ݿ����";
						strcpy(buf, "���������ݿ����");
						return;
					}

					// ��ȡ���û���ʤ�ֺ��ܾ���
					/*char** sqlResult;
					int nRow, nColumn;
					char* errMsg;*/
					sql = "SELECT win_round, total_round FROM Login WHERE id = " + to_string(id);
					if (sqlite3_get_table(db, sql.c_str(),&sqlResult,&nRow,&nColumn,&errMsg) != SQLITE_OK)
					{
						cout << "Endpoint[" << id << "]: sqlite error:" << *errMsg << endl;
						sqlite3_free(errMsg);
						strcpy(buf, "���������ݿ����");
						return;
					}
					endpoint->setWinRound(atoi(sqlResult[2]));
					endpoint->setTotalRound(atoi(sqlResult[3]));

					// �ڲ�ͬ�߳��в�����endpoints����˼Ӹ���
					hub_mute.lock();
					endpoints.push_back(endpoint);
					hub_mute.unlock();

					// ��һ���̹߳���endpoint
					thread endpointHandlerThread(&Hub::endpointHandler,this,endpoint);
					// Hub��ֹ��Endpoint������ֹ
					endpointHandlerThread.detach();
					
					// ���ظ�ʽ <port> <id>
					string sendbuf = to_string(endpointPort) + " " + to_string(id) + " " + to_string(endpoint->getWinRound()) + " " + to_string(endpoint->getTotalRound());
					strcpy(buf, sendbuf.c_str());
					cout << username << "��¼�ɹ����˿ں�Ϊ:" << sendbuf << endl;

				}
			}

		}
		/*************����ע��**************/
		else if (strs[0] == "logon")
		{
			cout << "��������: " << strs[0];
			cout << "\t�û���: " << strs[1];
			cout << "\t����: " << strs[2]<<endl;
			//������
			string username = strs[1];
			string password = strs[2];
			
			// ֱ�Ӳ������ݿ⣬���Ƿ��ظ�
			string sql = "INSERT INTO Login (username, password, online, win_round, total_round) VALUES ('" + username + "', '" + password + "', " + 
				to_string(0)+", "+ to_string(0)+", " + to_string(0)+");";
			if (sqlite3_exec(db, sql.c_str(), sqlite3_nonusecallback, NULL, &errMsg) != SQLITE_OK)
			{
				if (strcmp(errMsg, "UNIQUE constraint failed: Login.username") == 0)
				{
					cout << "Hub: Sqlite3 error: �û���" << username << "�ظ�" << endl;
					sqlite3_free(errMsg);
					strcpy(buf, "�û����ѱ�ռ�ã����޸��û���!");
					return;
				}
				cout << "Hub: Sqlite3 error: " << errMsg << endl;
				sqlite3_free(errMsg);
				strcpy(buf, "���������ݿ����");
				return;
			}

			// ��øղ�����û���id
			sql = "SELECT id FROM Login WHERE username = '" + strs[1] + "' AND password = '" + strs[2] + "'";
			char **sqlResult;
			int nRow, nColumn;
			if (sqlite3_get_table(db, sql.c_str(), &sqlResult, &nRow, &nColumn, &errMsg) != SQLITE_OK)
			{
				cout << "Hub: Sqlite3 error: " << errMsg << endl;
				sqlite3_free(errMsg);
				strcpy(buf, "���������ݿ����");
				return;
			}

			// ���������С����
			srand((unsigned)time(NULL));
			for (int i = 0; i < 3; i++)
			{
				// ��ø��û�id
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
					strcpy(buf, "���������ݿ����");
					return;
				}

			}
			cout << username << "ע��ɹ���" << endl;
			strcpy(buf, "Accept!\n");
		}
		else
		{
			strcpy(buf, "��Ч����!");
			cout << "��Ч����" << endl;
		}
	}
}

// ����ÿһ��endpoint
void Hub::endpointHandler(Endpoint *const endpoint)
{
	// endpoint����ִ��
	endpoint->process();

	// ��;�˳����޷��޸�online״̬
	// �޸����ݿ�online�ֶ�
	int _PlayerID = endpoint->getPlayerID();
	char *errMsg;
	string sql = "UPDATE Login SET online = 0 WHERE id = " + to_string(_PlayerID);
	if (sqlite3_exec(db, sql.c_str(), sqlite3_nonusecallback, NULL, &errMsg) != SQLITE_OK)
	{
		cout << "Endpoint[" << _PlayerID << "]: sqlite error:" << *errMsg << endl;
		sqlite3_free(errMsg);
		//buf2 = "���������ݿ����";
		strcpy(buf, "���������ݿ����");
		return;
	}

	// endpoint�˳�
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