#include "server.h"
using namespace std;

//int main()
//{
//	srand((unsigned int)time(NULL));
//	int autofight = 1;
//	Race<0> race0;
//	Race<1> race1;
//	Race<2> race2;
//	Race<3> race3;
//
//	Pokemon p0(race0, "LALA3");
//	Pokemon p1(race1, "¶«ÎÄ");
//	Pokemon p2(race2, "Po¸ç");
//	Pokemon p3(race3, "lwm");
//
//	while (true)
//	{
//		int x = rand() % 6;
//		if (x == 0)
//		{
//			BattleController battle(p0, p1, autofight);
//			battle.startBattle();
//		}
//		else if (x == 1)
//		{
//			BattleController battle(p0, p1, autofight);
//			battle.startBattle();
//		}
//		else if (x == 2)
//		{
//			BattleController battle(p3, p0, autofight);
//			battle.startBattle();
//		}
//		else if (x == 3)
//		{
//			BattleController battle(p1, p2, autofight);
//			battle.startBattle();
//		}
//		else if (x == 4)
//		{
//			BattleController battle(p1, p3, autofight);
//			battle.startBattle();
//		}
//		else if (x == 5)
//		{
//			BattleController battle(p2, p3, autofight);
//			battle.startBattle();
//		}
//		system("pause");
//	}
//	return 0;
//}

int main()
{
	Hub hub;
	hub.run();
	return 0;
}