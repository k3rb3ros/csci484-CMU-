#include"connection.h"

connection::connection()
{
	recieve = NULL;
	send = NULL;
	status = -1; //not connected
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

void connection::send_data(char* data)
{
	char  header[4];
	unsigned int len = strlen(data) + 1;

	SDLNet_Write32(len, header); //Write the length of the message to the header
	if(SDLNet_TCP_Send(client, header, 4) == 4) SDLNet_TCP_Send(client, data, len); //Send it
	else cout << "Error sending header" << endl;
}

char* connection::receive()
{
	char header[4];
	unsigned int len;

	while(1)
	{
		if(SDLNet_TCP_Recv(server, header, 4) == 4)
		{
			len = SDLNet_Read32(header); //Get header if succesfull read data
		 	recieve = (char*)calloc(len, sizeof(char));
			SDLNet_TCP_Recv(server, recieve, len);
			cout << recieve << endl;
			free(recieve);
		}
	}
	return NULL;
}

