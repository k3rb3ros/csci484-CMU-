#include "connection.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

char* getLINE()
{
	static char c[260];
	char c2 = 0;
	int i = 0;
	do
	{
		c2 = getchar();
		c[i++] = c2;
	}
	while((c2 != '\n') && (i < 259));
	c[i-1] = 0;
	return c;
}

int main(int argc, char** argv)
{

	char* message;
	string username = "k3rb3ros";
	if(SDL_Init(0) == -1) return 1;
	if(SDLNet_Init() == -1) return 2;
	connection test;
	cout << "status of connection " << test.get_cl_status() << ", " << test.get_srv_status() << endl;
	test.connect_server(6669);
	test.connect_client("127.0.0.1", 6669);
	cout << "status of connection " << test.get_cl_status() << ", " << test.get_srv_status() << endl;
	while(strcmp(message, "^close^") != 0)
	{
		//cout << username << ": ";
		message = getLINE();
		test._send(message);
	}
	test.close_client();
	test.close_server();
	SDLNet_Quit();
	SDL_Quit();
	return 0;
}
