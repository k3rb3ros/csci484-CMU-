#include "test_crypt.h"
using namespace std;

void test_crypt()
{
	unsigned char entropy [1024];
	//unsigned long int size = 0;
	int err = 0;
	rsa_key pub_key;
	//rsa_key priv_key;
	prng_state random_gen;

	for(int i=0; i<1024; i++) entropy[i] = 0; //init entropy

	if((err = sprng_start(&random_gen)) != CRYPT_OK) //start the rng and check for errors
	{
		cout << "start error " << error_to_string(err) << endl;
	}
	
	//if((err = sprng_add_entropy((unsigned const char*)"Hurpa Derp", 10 , &random_gen)) != CRYPT_OK)
	//{
	//	cout << "Add_entropy error " << error_to_string(err) << endl;	
	//}
	
	if((err = sprng_ready(&random_gen)) != CRYPT_OK)
	{
		cout << "Ready error " << error_to_string(err) << endl;
	}

	//sprng_read(entropy, size, &random_gen);
	
	if((err = rsa_make_key(&random_gen, 0, 1024, 65537, &pub_key)) != CRYPT_OK) //fcn is not working
	{
		cout << "RSA Key Generation error " << error_to_string(err) << endl;
	}
	sprng_done(&random_gen);
}
