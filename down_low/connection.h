/*A class containing all the requried SDLNet functions to connect to another client and 
to accept connect a connection from another chat client */
#include<SDL/SDL.h>
#include<SDL/SDL_net.h>
class connection
{
	public:
	
	connection(); //Connect default constructor
	connection(IPaddress hostname, Uint16 port); //Connect knowing ip of client , server and port

	void close(); //close the connection
	void connect(char* host); //connect to the server at the ip address passed assume default port
	void connect(char* host, Uint16 _port); //connect to server at the address at the port specified

	IPaddress get_ip(); //Get local ip
	IPaddress get_remote_ip(); //Get server ip
	int get_status();
	char* get_con_error();
	
	void send_data(char* data, int length); //Send data with the length of the data
	char* receive();

	private:

	char* recieve;
	char* send;
	int status;
	IPaddress ip;
	IPaddress remote_ip;
	TCPsocket client;
	TCPsocket server;
	Uint16 port;
};
