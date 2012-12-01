#include"connection.h"

connection::connection()
{
	receive = NULL;
	send = NULL;
	cl_is_alive = false;
	srv_is_alive = false;
	cl_status = -1; 
	srv_status = -1;
	client = NULL;
	server = NULL;
	port = 6669;
}

void connection::close_client()
{
	cl_is_alive = false;
	SDL_WaitThread(cl_thread, 0);
	SDLNet_TCP_Close(client);
}

void connection::close_server()
{
	srv_is_alive = false;
	SDL_WaitThread(srv_thread, 0);
	SDLNet_TCP_Close(server);
}

Uint32 get_ip(void* _c)
{
	connection* c = (connection*)_c;
	return c -> ip.host;
}

Uint32 get_remote_ip(void* _c)
{
	connection* c = (connection*)_c;
	return c -> remote_ip.host;
}

int spawn_client(void* _connection)
{
	connection* c = (connection*)_connection;
	char header[4];
	int length = -1;
	cout << "\nClient Running\n";
	while(c -> cl_is_alive)
	{
		if(c -> cl_status == 2 && strcmp(c -> send, "^close^") != 0)//If the message isn't the close command then continue
		{
			length = (strlen(c -> send)+1); //Get the length of the message
			SDLNet_Write32(length, header);
			if(SDLNet_TCP_Send(c -> client, header, 4) == 4) //Send header and check that send succeaded
			{
				if(SDLNet_TCP_Send(c -> client, c -> send, length) == length) c -> cl_status = 1; //Send the data if success then set the status to 1 
				for(int i=0; i<260; i++) c -> send[i] = 0;
			}
			else
			{
				c -> cl_status = -3;
			}
		}
		SDL_Delay(10);
	}
	cout << "Client closeing\n";
	return 0;
}

int spawn_server(void* _connection)
{
	connection* c = (connection*)_connection;
	char header[4];
	TCPsocket chclient = NULL;
	int length = -1;
	if(!chclient) c -> srv_status = 1;
	while(!chclient)
	{
		chclient = SDLNet_TCP_Accept(c -> server);
		SDL_Delay(10);
	}
	cout << "\nServer running\n";
	c -> srv_status = 2;
	while(c -> srv_is_alive)
	{
		if(c -> srv_status == 2)
		{
			if(SDLNet_TCP_Recv(chclient, header, 4) != 4)
			{
				cout << "\nError Recieving Header\n";
				c -> srv_status = -3;
			}
			else
			{
				length = SDLNet_Read32(header);
				c -> srv_status = 3;
			}
		}
		else if(c -> srv_status == 3)
		{
			c -> receive = new char[length];
			if(SDLNet_TCP_Recv(chclient, c -> receive, length))
			{
				c -> srv_status = 2;
				cout << "\nMessage: " << c -> receive << endl; //Output the message 
			}
			else c -> srv_status = -4; //error recieveing message
			delete []  c -> receive; //consider getting rid of me
		}
		SDL_Delay(10);
	}
	cout << "Server closing\n";
	SDLNet_TCP_Close(chclient);
	return 0;
}

void connection::connect_client(char* host)
{
	cl_status = 1;
	if(SDLNet_ResolveHost(&remote_ip, host, 6669) == -1) cl_status = -1; //Resolve the host of client
	client = SDLNet_TCP_Open(&remote_ip);//Open a TCP Socket for client
	if(!client) cl_status = -2;
	if(cl_status == 1)
	{
		cl_is_alive = true;
		cl_thread = SDL_CreateThread(spawn_client, this); //Spawn Client thread
	}
}

void connection::connect_client(char* host, Uint16 _port)
{
	cl_status = 1;
	if(SDLNet_ResolveHost(&remote_ip, host, _port) == -1) cl_status = -1; //Resolve the host of client
	client = SDLNet_TCP_Open(&remote_ip);//Open a TCP Socket for client
	if(!client) cl_status = -2;
	if(cl_status == 1)
	{
		cl_is_alive = true;
		cl_thread = SDL_CreateThread(spawn_client, this); //Spawn Client thread
	}
}

void connection::connect_server()
{
	srv_status = 1;
	if(SDLNet_ResolveHost(&ip, NULL, 6669) == -1) srv_status = -1; //Resolve the host of the server
	server = SDLNet_TCP_Open(&ip); //Open a TCP socket for the server
	if(!server) srv_status = -2;
	if(srv_status == 1)
	{
		srv_is_alive = true;
		srv_thread = SDL_CreateThread(spawn_server, this); //Spawn server thread
	}
}

void connection::connect_server(Uint16 _port)
{
	srv_status = 1;
	port = _port;
	if(SDLNet_ResolveHost(&ip, NULL, port) == -1) srv_status = -1; //Resolve the host of the server
	server = SDLNet_TCP_Open(&ip); //Open a TCP socket for the server
	if(!server) srv_status = -2;
	if(srv_status == 1)
	{
		srv_is_alive = true;
		srv_thread = SDL_CreateThread(spawn_server, this); //Spawn server thread
	}
}

int connection::get_cl_status()
{
	return cl_status;
}

int connection::get_srv_status()
{
	return srv_status;
}

char* connection::get_con_error()
{
	return NULL;
}

void connection::_send(char* data)//Fix Me
{
	send = data;
	cl_status = 2;
}

void connection::_receive()//Fix Me
{
	if(receive != NULL)
	{
		cout << receive << endl;
		receive = NULL;
	}
	else cout << "\nNothing in buffer\n";
}

