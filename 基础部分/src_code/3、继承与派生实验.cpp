#include <cmath>
#include <iostream>
using namespace std;

class Shape
{
public:
	Shape() { cout << "����ִ��Shape�Ĺ��캯��" << endl; }
	~Shape() { cout << "����ִ��Shape����������" << endl; }

	int cal_area()
	{
		cout << "����ִ��Shape�ļ����������" << endl;
		return 0;
	}
};

class Rectangle :public Shape
{
private:
	int m_x;
	int m_y;
public:
	Rectangle(int x,int y) { 
		cout << "����ִ��Rectangle�Ĺ��캯��" << endl; 
		m_x = x;
		m_y = y;
	}
	~Rectangle() { cout << "����ִ��Rectangle����������" << endl; }
	int cal_area() { 
		cout << "����ִ��Rectangle�ļ����������" << endl;
		return m_x * m_y;
	};
	
};

class Circle :public Shape
{
private:
	double m_r;
public:
	Circle(int r) { 
		cout << "����ִ��Circle�Ĺ��캯��" << endl; 
		m_r = r;
	}
	~Circle() { cout << "����ִ��Circle����������" << endl; }
	double cal_area() { 
		cout << "����ִ��Circle�ļ����������" << endl;
		return pow(m_r,2)*3.1415; 
	};
};

class Square :public Rectangle
{
private:
	int m_x;
public:
	Square(int x):Rectangle(x,x) { 
		cout << "����ִ��Square�Ĺ��캯��" << endl; 
		m_x = x;
	}
	~Square() { cout << "����ִ��Square����������" << endl; }
	int cal_area() { 
		cout << "����ִ��Square�ļ����������" << endl;
		return pow(m_x, 2);
	};
};

int main()
{
	Square s(3);
	cout << "s�������:" << s.cal_area() << endl;
	cout << "s�������:" << s.Rectangle::cal_area() << endl;
	Rectangle r(3, 4);
	cout << "r�������:"<<r.cal_area() << endl;
	Circle c(3);
	cout << "c�������:" << c.cal_area() << endl;

	system("pause");
	return 0;
}