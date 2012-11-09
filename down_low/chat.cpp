#include "connection.h"
#include <iostream>
using namespace std;

int main(int argc, char** argv)
{

	if(SDL_Init(0) == -1) return 1;
	if(SDLNet_Init() == -1) return 2;
	connection test;
	cout << "status of connection " << test.get_status() << endl;
	cout << "Whatever" << endl;
	test.connect("localhost", 9999);
	test.close();
	SDLNet_Quit();
	SDL_Quit();
	return 0;
}
