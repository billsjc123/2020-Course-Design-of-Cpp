#include <iostream>
using namespace std;

int ** init_matrix()
{
	int **matrix = new int*[4];
	for (int i = 0; i < 4; i++)
	{
		matrix[i] = new int[5];
	}
	cout << "������4*5�ľ���\n";
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cin >> matrix[i][j];
		}
	}
	return matrix;
}

void print_matrix(int **matrix)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout<< matrix[i][j]<<'\t';
		}
		cout << endl;
	}
}

void del_matrix(int **matrix)
{
	for (int i = 0; i < 4; i++)
	{
		delete []matrix[i];
	}
	delete []matrix;
}

int ** add_matrix(int **A1, int ** A2)
{
	cout << "------------ִ�о���ӷ�------------" << endl;

	int **A3 = new int*[4];
	for (int i = 0; i < 4; i++)
	{
		A3[i] = new int[5];
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			A3[i][j] = A1[i][j] + A2[i][j];
		}
	}
	return A3;
}

int ** sub_matrix(int **A1, int ** A2)
{
	cout << "------------ִ�о������------------" << endl;

	int **A3 = new int*[4];
	for (int i = 0; i < 4; i++)
	{
		A3[i] = new int[5];
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			A3[i][j] = A1[i][j] - A2[i][j];
		}
	}
	return A3;
}



int main()
{
	//����1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
	
	//��̬����A1��A2
	int ** A1 = init_matrix();
	print_matrix(A1);
	int ** A2 = init_matrix();
	print_matrix(A2);

	//���㲢���A3 = A1 + A2
	int ** A3 = add_matrix(A1, A2);
	print_matrix(A3);
	//���㲢���A3 = A1 - A2
	A3 = sub_matrix(A1, A2);
	print_matrix(A3);

	//�ͷž���ռ�
	del_matrix(A1);
	del_matrix(A2);
	del_matrix(A3);
	system("pause");
	return 0;
}