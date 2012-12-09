#include "headers/test_crypt.h"
#include "stdio.h"
using namespace std;

void print_buff(unsigned char* buff, unsigned long int len)
{
	for(unsigned long int i = 0; i < len; i++) cout << buff[i];
}

void test_crypt()
{
	#define keysize 2048
	int err = 0;
	int rng_idx = -1; //rng index
	int hash_idx = -1; //hasd index
	ltc_mp = tfm_desc; //register tomsfast math
	rsa_key key_pair; //rsa key pair
	prng_state sprng; //prng descriptor
	unsigned char m1[32], m2[32], out[keysize];
	unsigned long int s_len = -1;
	
	if(register_prng(&sprng_desc) == -1) //register prng
	{
		cout << "Error registering prng " << endl;
	}
	
	if (register_hash(&sha256_desc) == -1)
	{
		printf("Error registering sha256");
	}
	
	if((err = sprng_start(&sprng)) != CRYPT_OK) //start the rng and check for errors
	{
		cout << "start error " << error_to_string(err) << endl;
	}
	
	rng_idx = find_prng("sprng"); //index the prng so that rsa fcns can use it
	hash_idx = find_hash("sha256");

	if((err = sprng_ready(&sprng)) != CRYPT_OK) //Check that the rng is ready
	{
		cout << "Ready error " << error_to_string(err) << endl;
	}

        
	if((err = rsa_make_key(&sprng,         	//PRNG state  //generate rsa pub/private keypair
			       rng_idx,        	//PRNG idx
			       keysize/8,       //Size of key
			       65537,          	//e
			       &key_pair)      	//RSA key
				) != CRYPT_OK) 	//if conditon test
	{
		cout << "RSA Key Generation error " << error_to_string(err) << endl; 
	}
	else 
	{
		cout << "Private key: " << key_pair.d << endl;
		cout << "Public key: " << key_pair.e << endl;
	}

	//Attemping RSA encrypt
	
	for (int i = 0; i< keysize; i++) out[i] = 0; //init out buffer
	s_len = sizeof(out);
	cout << s_len << endl;
  	strcpy((char*)m1, "Hey hows it going");
	cout << "Pre-encrypted M1: " << m1 << endl;
	if((err = rsa_exptmod(	m1,		//Our message
				32, 		//is 32 bytes
				out, 		//Output buffer
				&s_len, 	//Output length
				PK_PUBLIC, 	//Encrypt mode
				&key_pair) 	//Our rsa keypair
	   )			 != CRYPT_OK)

	{
		cout << "rsa_encrypt key " << error_to_string(err);
	}
	else 
	{
		cout << "Strcmpr test " << strcmp((const char*)out, (const char*)"\0") << endl;
		cout << "Message sucessfully rsa encrypted {";
		print_buff(out, keysize);
		cout << "}\n";
	}

	if(err != CRYPT_OK)rsa_free(&key_pair); //free the key when we are done with it;
	sprng_done(&sprng); //done generating random numbers
}
