#include "headers/test_crypt.h"
using namespace std;

void test_crypt()
{
	int err = 0;
	int rng_idx = -1; //rng index, not sure if I need this
	ltc_mp = tfm_desc; //tell tomcrypt to use toms fast math
	rsa_key pub_key;
	prng_state random_gen;


	if((err = sprng_start(&random_gen)) != CRYPT_OK) //start the rng and check for errors
	{
		cout << "start error " << error_to_string(err) << endl;
	}
	
	rng_idx = find_prng("SPRNG");

	if((err = sprng_ready(&random_gen)) != CRYPT_OK)
	{
		cout << "Ready error " << error_to_string(err) << endl;
	}

	//test toms fast math present and working
	
        
	if((err = rsa_make_key(&random_gen,           //PRNG state
			       rng_idx,        //PRNG idx
			       1024/8,         //Size of key
			       65537,          //e
			       &pub_key)       //RSA key
				) != CRYPT_OK) //if conditon test
	{
		cout << "RSA Key Generation error " << error_to_string(err) << endl;
	}
	if(err != CRYPT_OK)rsa_free(&pub_key); //free the key when we are done with it;
	sprng_done(&random_gen); //done generating random numbers
}
