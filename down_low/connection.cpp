#include"connection.h"

connection::connection()
{
	recieve = NULL;
	send = NULL;
	status = -1; //not initialized
	client = NULL;
	server = NULL;
	port = 6669;
}

void connection::close()
{
	SDLNet_TCP_Close(client);
	SDLNet_TCP_Close(server);
}

void connection::connect(char* host)
{
	status = 1;
	if(SDLNet_ResolveHost(&remote_ip, host, port) == -1) status = -2; //Resolve the host of client
	client == SDLNet_TCP_Open(&remote_ip);//Open a TCP Socket for client
	if(!client) status = -3;
	if(SDLNet_ResolveHost(&ip, NULL, port) == -1) status = -4; //Resolve the host of the server
	server = SDLNet_TCP_Open(&ip); //Open a TCP socket for the server
	if(!server) status = -5;
	if(status == 1); //spawn thread;
}

void connection::connect(char* host, Uint16 _port)
{
	status = 1;
	port = _port;
	if(SDLNet_ResolveHost(&remote_ip, host, port) == -1) status = -2; //Resolve the host of client
	client == SDLNet_TCP_Open(&remote_ip);//Open a TCP Socket for client
	if(!client) status = -3;
	if(SDLNet_ResolveHost(&ip, NULL, port) == -1) status = -4; //Resolve the host of the server
	server = SDLNet_TCP_Open(&ip); //Open a TCP socket for the server
	if(!server) status = -5;
	if(status == 1); //spawn thread;
}

IPaddress connection::get_ip()
{
	return ip;
}

IPaddress connection::get_remote_ip()
{
	return remote_ip;
}

int connection::get_status()
{
	return 0;
}

char* connection::get_con_error()
{
	return NULL;
}

void connection::send_data(char* data, int length)
{

}

char* connection::receive()
{
	return NULL;
}

