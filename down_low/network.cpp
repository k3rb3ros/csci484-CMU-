//#############################
//#   Written by Ryan Morris  #
//#       (k3rb3ros)          #
//# In order to provide TCP   # 
//# network functionality for # 
//# chat program              #
//#############################
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_net.h>
#ifndef _MSC_VER
#include <unistd.h>
#endif
using namespace std;

const int MAXL = 1024;
char message[MAXL];
int len = 0;
IPaddress ip;
IPaddress* remoteip = NULL;
TCPsocket client;
Uint32 ipaddr;
Uint16 port;

bool init_net() //Init SDL and SDLnet return true on success
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		cout << "SDL_Init: " << SDL_GetError() << endl;
		return false;
	}
	if(SDLNet_Init() == -1)
	{
		cout << "SDLnet_Init: " << SDLNet_GetError() << endl; 
		return false;
	}
	else return true;
}

TCPsocket open_server_socket(IPaddress &ip, Uint16 port)//atempt to resolve host ip and open a server socket
{
	TCPsocket server;
	if((SDLNet_ResolveHost(&ip, NULL, port)) == -1)//Resolve the host requires a valid port
	{
		cout << "SDLnet_ResolveHost: " << SDLNet_GetError()  << endl;
		return NULL;
	}
	
	server = SDLNet_TCP_Open(&ip);//Open the server socket
	if(!server)
	{
		cout << "SDLnet_TCP_Open: " << SDLNet_GetError() << endl;
		return NULL; 
	}
	return server;
}
int main(int argc, char** argv)
{
	if(!init_net()) return 1;
	TCPsocket test = open_server_socket(ip, 6669);
	return 0;
}
