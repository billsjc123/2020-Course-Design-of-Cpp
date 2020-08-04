#include <cmath>
#include <iostream>
using namespace std;

class Matrix
{
	friend ostream& operator<<(ostream &cout, Matrix p);
	friend istream& operator>>(istream &cin, Matrix &p);
private:
	int m_lines;
	int m_rows;
	int **m_matrix;
public:
	char _id;
	void set_lines(int lines) { m_lines = lines; };
	void set_rows(int rows) { m_rows = rows; };
	int ** get_matrix(void) { return m_matrix; };
	int get_lines(void) { return m_lines; };
	int get_rows(void) { return m_rows; };
	Matrix(int row,int line)
	{
		m_rows = row;
		m_lines = line;
		cout << "����ִ��Matrix" << _id << "���вι��캯��" << endl;
		m_matrix = new int*[row];
		for (int i = 0; i < row; i++)
		{
			m_matrix[i] = new int[line];
		}
	}
	~Matrix()
	{
		cout << "����ִ��Matrix"<<_id<<"����������" << endl;
		int rows = get_rows();
		for (int i = 0; i < rows; i++)
		{
			delete[]m_matrix[i];
		}
		delete[]m_matrix;
	}
	Matrix(const Matrix &b)
	{
		m_rows = b.m_rows;
		m_lines = b.m_lines;
		_id = b._id;
		cout << "����ִ��Matrix" << _id << "�Ŀ������캯��" << endl;

		m_matrix = new int*[b.m_rows];
		for (int i = 0; i < b.m_rows; i++)
		{
			m_matrix[i] = new int[b.m_lines];
		}
		for (int i = 0; i < m_rows; i++)
		{
			for (int j = 0; j < m_lines; j++)
			{
				m_matrix[i][j]=b.m_matrix[i][j];
			}
		}
	}
	void input_matrix()
	{
		cout << "���������" << _id << "��ֵ" << endl;
		for (int i = 0; i < m_rows; i++)
		{
			for (int j = 0; j < m_lines; j++)
			{
				cin >> m_matrix[i][j];
			}
		}
	}
	void print_matrix()
	{
		cout << "�����������" << _id << "��ֵ" << endl;
		for (int i = 0; i < m_rows; i++)
		{
			for (int j = 0; j < m_lines; j++)
			{
				cout << m_matrix[i][j] << '\t';
			}
			cout << endl;
		}
	}
	Matrix add_matrix(Matrix b)
	{
		cout << "����ִ�о���" << _id << "�ļӷ�" << endl;
		Matrix d(m_rows, m_lines);
		if (!(m_rows == b.get_rows() && m_lines == b.get_lines()))
		{
			cout << "���������С��һ�£�" << endl;
			return d;
		}
		int **d_matrix = d.get_matrix(), **b_matrix = b.get_matrix();
		for (int i = 0; i < m_rows; i++)
		{
			for (int j = 0; j < m_lines; j++)
			{
				d_matrix[i][j] =  b_matrix[i][j]+m_matrix[i][j];
			}
		}
		return d;
	}

	Matrix sub_matrix(Matrix b)
	{
		cout << "����ִ�о���" << _id << "�ļ���" << endl;
		Matrix d(m_rows, m_lines);
		if (!(m_rows == b.get_rows() && m_lines == b.get_lines()))
		{
			cout << "���������С��һ�£�" << endl;
			return d;
		}
		int **d_matrix = d.get_matrix(), **b_matrix = b.get_matrix();
		for (int i = 0; i < m_rows; i++)
		{
			for (int j = 0; j < m_lines; j++)
			{
				d_matrix[i][j] = -(b_matrix[i][j] - m_matrix[i][j]);
			}
		}
		return d;
	}

	// �ع��Ⱥţ�ʵ�����
	Matrix& operator=(const Matrix &b)
	{
		//���ͷŸɾ���������Ķ���

		//������Ը�ֵ
		if (this != &b)
		{
			if (m_matrix)
			{
				for (int i = 0; i < m_rows; i++)
				{
					delete[]m_matrix[i];
				}
				delete[]m_matrix;
			}

			//���
			m_matrix = new int*[b.m_rows];
			for (int i = 0; i < b.m_rows; i++)
			{
				m_matrix[i] = new int[b.m_lines];
			}
			for (int i = 0; i < m_rows; i++)
			{
				for (int j = 0; j < m_lines; j++)
				{
					m_matrix[i][j] = b.m_matrix[i][j];
				}
			}
		}
		return *this;
	}

	Matrix operator+(Matrix &b)
	{
		cout << "------------ִ�о���ӷ�------------" << endl;
		Matrix d(m_rows, m_lines);
		if (!(m_rows == b.get_rows() && m_lines == b.get_lines()))
		{
			cout << "���������С��һ�£�" << endl;
			return d;
		}
		int **d_matrix = d.get_matrix(), **b_matrix = b.get_matrix();
		for (int i = 0; i < m_rows; i++)
		{
			for (int j = 0; j < m_lines; j++)
			{
				d_matrix[i][j] = b_matrix[i][j] + m_matrix[i][j];
			}
		}
		return d;
	}

	Matrix operator-(Matrix &b)
	{
		cout << "------------ִ�о������------------" << endl;
		Matrix d(m_rows, m_lines);
		if (!(m_rows == b.get_rows() && m_lines == b.get_lines()))
		{
			cout << "���������С��һ�£�" << endl;
			return d;
		}
		int **d_matrix = d.get_matrix(), **b_matrix = b.get_matrix();
		for (int i = 0; i < m_rows; i++)
		{
			for (int j = 0; j < m_lines; j++)
			{
				d_matrix[i][j] = -(b_matrix[i][j] - m_matrix[i][j]);
			}
		}
		return d;
	}
};

ostream& operator<<(ostream &cout, Matrix p)
{
	cout << "�����������" << p._id << "��ֵ..." << endl;
	for (int i = 0; i < p.m_rows; i++)
	{
		for (int j = 0; j < p.m_lines; j++)
		{
			cout << p.m_matrix[i][j] << '\t';
		}
		cout << endl;
	}
	return cout;
}

istream& operator>>(istream &cin, Matrix &p)
{
	cout << "���������" << p._id << "��ֵ..." << endl;
	int ** m = p.get_matrix();
	for (int i = 0; i < p.get_rows(); i++)
	{
		for (int j = 0; j < p.get_lines(); j++)
		{
			cin >> m[i][j] ;
		}
	}
	return cin;
}


int main()
{
	// A1 1 2 3 4 5 6 7 8 9 10 11 12
	// A2 12 11 10 9 8 7 6 5 4 3 2 1

	Matrix A1(3, 4), A2(3, 4), A3(3, 4);
	cin >> A1;
	cout << A1;
	A1 = A1;
	cout << A1;
	//cin >> A2;
	//cout << A2;
	///*A1.input_matrix();
	//A1.print_matrix();
	//A2.input_matrix();
	//A2.print_matrix();*/

	//A3 = A1 + A2;
	//cout << A3;
	//A3 = A1 - A2;
	//cout << A3;

	//Matrix* pA1 = new Matrix(3, 4);
	//Matrix* pA2 = new Matrix(3, 4);
	//Matrix* pA3 = new Matrix(3, 4);
	//cin >> *pA1;
	//cout << *pA1;
	//cin >> *pA2;
	//cout << *pA2;
	///*pA1->input_matrix();
	//pA1->print_matrix();
	//pA2->input_matrix();
	//pA2->print_matrix();*/
	//*pA3 = *pA1 + *pA2;
	//cout << *pA3;
	//*pA3 = *pA1 - *pA2;
	//cout << *pA3;
	//delete pA1;
	//delete pA2;
	//delete pA3;
	system("pause");
	return 0;
}