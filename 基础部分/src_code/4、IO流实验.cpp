#include <cmath>
#include <iostream>
#include <time.h>
using namespace std;


//�������ĺϷ���
bool isint(char s[])
{
	for (int i = 0; s[i] != '\0'; i++)
		if (s[i]<1||s[i]>255||!isdigit(s[i]))
			return false;
	return true;
}

int main()
{
	srand(unsigned(time(NULL)));
	int ans = rand()%1000+1;
	while (1)
	{
		char input[100];
		int guess = 0;
		cout << "��²���Ʒ�ļ۸�" << endl;
		if (cin >> input && !isint(input))
		{
			cout << "������Ч��������1-1000��Χ�ڵ�������" << endl;
			getchar();
			continue;
		}
		guess = atoi(input);

		if (guess > 1000 || guess < 1)
		{
			cout << "���ݷ�Χ����������1-1000��Χ�ڵ�������" << endl;
			continue;
		}

		if (guess > ans) {
			if (guess - ans < 100)
				cout << "�µļ۸����һ���" << endl;
			else if(guess -ans<300)
				cout << "�µļ۸����ͦ��" << endl;
			else
				cout << "�µļ۸���˷ǳ���" << endl;
		}
		else if (guess < ans) {
			if (ans - guess < 100)
				cout << "�µļ۸����һ���" << endl;
			else if (ans - guess < 300)
				cout << "�µļ۸����ͦ��" << endl;
			else
				cout << "�µļ۸���˷ǳ���" << endl;
		}
		else
		{
			cout << "��ϲ��¶��ˣ�����" << endl;
			break;
		}
	}
	system("pause");
	return 0;
}