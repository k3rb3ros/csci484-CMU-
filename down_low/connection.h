/*A class containing all the requried SDLNet functions to connect to another client and 
to accept connect a connection from another chat client */
#include<SDL/SDL.h>
#include<SDL/SDL_net.h>
#include<SDL/SDL_thread.h>
#include<iostream>
using namespace std;
class connection
{
	public:
	
	connection(); //Connect default constructor
	connection(IPaddress hostname, Uint16 port); //Connect knowing ip of client , server and port

	void close_client();
	void close_server();
	void connect_client(char* host);
	void connect_client(char* host, Uint16 _port);
	void connect_server(); //connect to the server at the ip address passed assume default port
	void connect_server(Uint16 _port); //connect to server at the address at the port specified
	
	//IPaddress get_ip(); //Get local ip
	//IPaddress get_remote_ip(); //Get server ip
	int get_cl_status(); 
	int get_srv_status();
	char* get_con_error(); //Display an error message consider removing me
	
	void _send(char* data); //Send data to the client
	void _receive(); //Recieve data from server

	//private:

	//IPaddress ip;
	//IPaddress remote_ip;
	
	protected:
	
 	friend Uint32 get_ip(void* _c); //Get local ip
	friend Uint32 get_remote_ip(void* _c); //Get server ip
	friend int spawn_client(void* _c); //Spawn the client thread and pass it an instance of the connection object
	friend int spawn_server(void* _c); //Spawn the server thread and pass it an instance of the connection object
	
	bool cl_is_alive;
	bool srv_is_alive;
	char* receive;
	char* send;
	IPaddress ip;
	IPaddress remote_ip;
	int cl_status;
	int srv_status;
	SDL_Thread* cl_thread;
	SDL_Thread* srv_thread;
	TCPsocket client;
	TCPsocket server;
	Uint16 port;
};
