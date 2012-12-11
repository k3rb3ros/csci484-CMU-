#include "headers/crypt.h"

int init_twofish(unsigned char* _iv, unsigned char* _key) //init twofish cipher
{
	if(register_cipher(&twofish_desc) == -1) //register twofish
	{
		cerr << "Unable to register Twofish Cipher\n";
	}

	if((ERR = ofb_start(find_cipher("twofish"), _iv, _key, BLOCKSIZE, ROUNDS,  &OFB)) != CRYPT_OK) //start ctr mode
	{
		cerr << "Error starting ofb mode " << error_to_string(ERR) << endl;	
	}
	return ERR;
}

int encrypt_twofish(unsigned long int* _plain, unsigned long int* _cipher)
{
	ERR = ofb_encrypt((unsigned char*)_plain, (unsigned char*)_cipher, ROUNDS, &OFB); //encrypt the data
	return ERR;
}
int decrypt_twofish(unsigned long int* _cipher, unsigned long int* _plain)
{
	ofb_setiv(IV, BLOCKSIZE, &OFB); //reset the initialization vector
	ERR = ofb_decrypt((unsigned char*)_cipher, (unsigned char*)_plain, ROUNDS, &OFB); //decrypt the data
	return ERR;
}

void done()
{
	twofish_done(&TF_KEY);
}
