#include <iostream>
#include <cmath>
using namespace std;

class Point {
private:
	int _x;
	int _y;
public:
	
	Point(int x,int y);
	Point();
	Point(const Point & p);
	~Point() { cout << "Point���ڵ�����������..." << endl; };
	void set_x(int x) { _x = x; }
	void set_y(int y) { _y = y; }
	int get_x(void) { return _x; }
	int get_y(void) { return _y; }
	double cal_distance(Point a);
};

Point::Point(int x, int y)
{
	cout << "Point���ڵ����вι��캯��..." << endl;
	_x = x, _y = y;
}
Point::Point()
{
	cout << "Point���ڵ����޲ι��캯��..." << endl;
	_x = 0, _y =0;
}
Point::Point(const Point & p)
{
	cout << "Point���ڵ��ÿ������캯��..." << endl;
	_x = p._x, _y = p._y;
}

double Point::cal_distance(Point a)
{
	int ax = a.get_x(), ay = a.get_y();
	int bx = _x, by = _y;

	return sqrt(pow(ax - bx, 2) + pow(ay - by, 2));

}

class Circle {
private:
	Point m_center;
	float m_radius;
public:
	void set_r(float r) 
	{
		m_radius = r;
	};
	float get_r() 
	{ 
		return m_radius; 
	};
	void set_center(Point center)
	{
		m_center = center;
	};
	Point get_center()
	{
		return m_center;
	}
	Circle();
	Circle(int px, int py, int r);
	Circle(const Circle &c);
	~Circle() { cout << "���ڵ���" << "Բ��Ϊ" << m_center.get_x() << " " << m_center.get_y() << "��Circle����������..." << endl; };
};

Circle::Circle()
{
	//cout << "���ڵ���" << "Բ��Ϊ" << x << " " << y << "��Circle���޲ι��캯��..." << endl;

	int x, y, r;
	cout << "������Բ������ĺ����꣺";
	cin >> x;
	cout << "������Բ������������꣺";
	cin >> y;
	cout << "���ڵ���" << "Բ��Ϊ" << x << " " << y << "��Circle���޲ι��캯��..." << endl;
	cout << "������Բ�İ뾶��";
	cin >> m_radius;
	m_center = Point(x, y);
}

Circle::Circle(int px, int py, int r) :m_center(px, py)
{
	cout << "���ڵ���" << "Բ��Ϊ" << px << " " << py << "��Circle���вι��캯��..." << endl;

	m_radius = r;
}

Circle::Circle(const Circle &c)
{
	cout << "���ڵ���Circle�Ŀ������캯��..." << endl;
	m_center = c.m_center;
	m_radius = c.m_radius;
}

bool intersect(Circle &a,Circle &b)
{
	double dist = a.get_center().cal_distance(b.get_center());
	// ��������Բ�������Ͱ��������
	if (dist >= a.get_r() + b.get_r()||dist<abs(a.get_r() + b.get_r()))
	{
		cout << "���ཻ" << endl;
		return 0;
	}
	else
	{
		cout << "�ཻ" << endl;
		return 1;
	}
}


int main()
{
	// �вι��캯��
	Circle a(0,0,1);
	Circle b(0,0,2);
	
	// �޲ι��캯��
	/*Circle a;
	Circle b;*/

	// �ж��ཻ
	bool is_intersect = intersect(a, b);

	system("pause");
	return 0;
}
