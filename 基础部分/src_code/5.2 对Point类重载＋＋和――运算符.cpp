#include <iostream>
#include <cmath>
using namespace std;

class Point {
	friend ostream& operator<<(ostream &cout, Point p);
private:
	int x;
	int y;
public:

	Point(int xx, int yy);
	~Point() { cout << "Point���ڵ�����������..." << endl; };
	void set_x(int xx) { x = xx; }
	void set_y(int yy) { y = yy; }
	int get_x(void) { return x; }
	int get_y(void) { return y; }
	double cal_distance(Point a);

	//ǰ��
	Point& operator++()
	{
		cout << "����ִ��ǰ��++����...\n";
		x++;
		y++;

		return *this; 
	}

	//����
	Point operator++(int)
	{
		cout << "����ִ�к���++����...\n";

		Point temp = *this;
		x++;
		y++;

		return temp;
	}

	Point& operator--()
	{
		cout << "����ִ��ǰ��--����...\n";

		x--;
		y--;

		return *this;
	}

	Point operator--(int)
	{
		cout << "����ִ�к���--����...\n";

		Point temp = *this;
		x--;
		y--;

		return temp;
	}
};

ostream& operator<<(ostream &cout,Point p)
{
	cout << "����ִ���������...\n";
	cout <<"��ʱx="<< p.x<< "��y=" << p.y << endl;
	cout << "-----------------------------------------------\n";

	return cout;
}

int main()
{
	Point p(3, 4);
	cout << p;
	cout << p++;
	cout << p;
	cout << ++p;
	cout << --p;
	system("pause");
	return 0;
}