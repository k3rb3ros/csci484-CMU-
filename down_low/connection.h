/*A class containing all the requried SDLNet functions to connect to another client and 
to accept connect a connection from another chat client */
class connection
{
	public:

	connection(); //Default contructor
	connection(IPaddress, IPaddress*, Uint16); //Connect knowing ip of client , server and port

	void close(); //close the connection
	void connect(IPaddress*); //connect to the server at the ip address passed assume default port
	void connect(IPaddress*, Uint16); //connect to server at the address at the port specified
	void connect(IPaddress, IPaddress*, Uint16); //same as constructor

	IPaddress get_ip(); //Get local ip
	IPaddress get_remote_ip(); //Get server ip
	int get_status();
	string get_con_error();
	
	void send_data(string, int); //Send data with the length of the data
	char* recieve();

	private:

	string data;
	int status;
	IPaddress ip;
	IPaddress* remoteip;
	TCPsocket client;
	TCPsocket server;
	Uint32 ipaddr;
	Uint16 port;

};
