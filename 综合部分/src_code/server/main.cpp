#include "server.h"
using namespace std;



int main()
{
	srand(time(NULL));
	Hub hub;
	hub.run();
	return 0;
}	