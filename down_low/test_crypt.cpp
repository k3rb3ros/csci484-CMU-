#include "headers/test_crypt.h"
#include "stdio.h"

#define ROUNDS 16
#define BLOCKSIZE 16 //128/8 = 16
using namespace std;

void print_buff(unsigned char* buff, unsigned long int len)
{
	for(unsigned long int i = 0; i < len; i++) cout << buff[i];
}

void init_buff(unsigned char* buff, unsigned long int len)
{
	for(unsigned long int i = 0; i < len; i++) buff[i] = 0;
}

//Treat my like gold
int init_twofish(unsigned char* iv, unsigned char* key, symmetric_OFB *ofb) //init twofish cipher
{
	int err = CRYPT_OK;
	if(register_cipher(&twofish_desc) == -1) //register twofish
	{
		cout << "Unable to register Twofish Cipher\n";
	}

	if((err = ofb_start(find_cipher("twofish"), iv, key, BLOCKSIZE, ROUNDS,  ofb)) != CRYPT_OK) //start ctr mode
	{
		cout << "Error starting ofb mode " << error_to_string(err) << endl;	
	}
	return err;
}

void test_twofish()
{
	symmetric_key tf_key;
	unsigned char pt[16], ct[16], key[16];
	int err;
	int keysize = 16;
	unsigned char iv[16];
	symmetric_OFB ofb;
	strcpy((char*)pt, "Attack at dawn9");
	strcpy((char*)key, "kz6JN2qblx7KM3w");
	strcpy((char*)iv, "Hurpa_Durpa");
	twofish_keysize(&keysize);
	
	init_twofish(iv, key, &ofb);

	//Read to go here
	cout << "Plaintext: " << pt << endl;
	cout << "Key: " << key << endl;
	ofb_encrypt(pt, pt, 16, &ofb);
	cout << "Ciphertext: " << ct << endl;
	cout << "Decrypting...\n"; 
	ofb_setiv(iv, 16, &ofb);
	ofb_decrypt(pt, pt, 16, &ofb);
	cout << "Resulttext: " << pt << endl;

	//Done
	twofish_done(&tf_key); //done here
}
void test_crypt()
{
 test_twofish();
}
void temp_crypt()
{
	
	#define KEYSIZE 2048
	int err = 0;
	int rng_idx = -1; //rng index
	int hash_idx = -1; //hash index
	int res = -1; //used to check the validity of data
	ltc_mp = tfm_desc; //register tomsfast math
	rsa_key me; //rsa key pair
	prng_state sprng; //prng descriptor
	unsigned char m1[32], m2[32], out[KEYSIZE];
	unsigned long int l1 = -1;
	unsigned long int l2 = -1;
	
	if(register_prng(&sprng_desc) == -1) //register prng
	{
		cout << "Error registering prng " << endl;
	}
	
	if(register_hash(&sha256_desc) == -1)
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

        //*******************************************************************************************************************************
	//Diffie helmann key exchangei
        //*******************************************************************************************************************************

	//my key
	if((err = rsa_make_key(&sprng,         	//PRNG state  //generate rsa pub/private keypair
			       rng_idx,        	//PRNG idx
			       KEYSIZE/8,       //Size of key
			       65537,          	//e
			       &me)      	//RSA key
				) != CRYPT_OK) 	//if conditon test
	{
		cout << "RSA Key Generation error " << error_to_string(err) << endl; 
	}
	else 
	{
		cout << "My Private key: " << me.d << endl;
		cout << "My Public key: " << me.e << endl;
	}
	unsigned char my_private[KEYSIZE];
	unsigned char my_public[KEYSIZE];
	init_buff(my_private, KEYSIZE);
	unsigned long int keylen = -1;
	keylen = KEYSIZE; //A quick way to standardize keysize
	//Export my private key to buffer
	if((err = rsa_export(my_private,		//Export buffer --> Send over network
			     &keylen,		//size of key (BYTES)
			     PK_PRIVATE,	//Export our public key to create the new shared key
			     &me)		//My public key
	   ) != CRYPT_OK)
	{
		cout << "Error exporting private key" << endl;
	}
	else
	{
		cout << "Private_key succesfully exported\n"; 
		/*
		cout << "My pub key: [[[";
		print_buff(my_private, (unsigned long int)KEYSIZE);
		cout << "]]] length of key " <<strlen((const char*)my_private) <<endl;
		*/
	}
	
	if((err = rsa_export(my_public,	//Export buffer --> Send over network
			     &keylen,		//size of key (BYTES)
			     PK_PUBLIC,		//Export our public key to create the new shared key
			     &me)		//My public key
	   ) != CRYPT_OK)
	{
		cout << "Error exporting public key" << endl;
	}
	else
	{
		cout << "There_key successfully exported\n";
		/*
		cout << "My pub key: [[[";
		print_buff(my_public, (unsigned long int)KEYSIZE);
		cout << "]]] length of key " <<strlen((const char*)my_private) <<endl;
		*/
	}
	//Export their key to buffer
	//
	//Imaginnary Diffie Helman exchange over network takes place 
	//My_Public Key --> ###Network### --> other person
	//Me <-- ###Network### <-- Their_Public Key
	
	//Mix their key with my key
	if((err = rsa_import(my_private, KEYSIZE, &me)) != CRYPT_OK)
	{
		cout << "Error importing my_private key to me" << endl;
	}
	else
	{
	}

	//Mix my key with their key
	if((err = rsa_import(my_public, KEYSIZE, &me)) != CRYPT_OK)
	{
		cout << "Error importing their_public key to me" << endl;
	}
	else
	{
	}

		cout << "Imported Private key: " << me.d << endl;
		cout << "Imported Public key: " << me.e << endl;
        //*******************************************************************************************************************************
	//Diffie helmann key exchange
        //*******************************************************************************************************************************


	//###############################################################################################################################
	//Working RSA encrypt decrypt
	//###############################################################################################################################
	//Attemping RSA encrypt
	
	for (int i = 0; i< KEYSIZE; i++) out[i] = 0; //init out buffer
	l1 = sizeof(out);
	cout << "Keysize (bits) " << l1 << endl;
  	strcpy((char*)m1, "Hey hows it going");
	cout << "Pre-encrypted M1: " << m1 << endl;
	if((err = rsa_encrypt_key(	m1,		//Our message
					32, 		//is 32 bytes
					out, 		//Output buffer
					&l1, 		//Output length
					NULL,		//lparam
					0,		//With a length of zero
					&sprng, 	//Our rng state
					rng_idx,	//Our rng index
					hash_idx,	//Our hash index
					&me) 	//Our rsa keypair
	   )			 != CRYPT_OK)

	{
		cout << "Encryption Error " << error_to_string(err);
	}
	else
	{
		cout << "Strcmpr test " << strcmp((const char*)out, (const char*)"\0") << endl;
		cout << "Message sucessfully rsa encrypted {" << out << "}\n";
	}

	//Attempting rsa decrypt
	if((err = rsa_decrypt_key(	out,		//Our message
					l1, 		//is 32 bytes
					m2, 		//Output buffer
					&l2, 		//Output length
					NULL,		//lparam
					0,		//With a length of zero
					hash_idx,	//Our hash index
					&res,		//Validity of data
					&me) 	        //There rsa keypair
	   )			 != CRYPT_OK)

	{
		cout << "Encryption Error " << error_to_string(err);
	}
	else if(res == 1)
	{
		cout << "Message sucessfully decrypted {" << m2 << "}\n";
	}
	else
	{
		cout << "Error message corrupted in transit\n";
	}

	//###############################################################################################################################
	//HERE
	//###############################################################################################################################

	if(err != CRYPT_OK)rsa_free(&me); //free the key when we are done with it;
	sprng_done(&sprng); //done generating random numbers
}
