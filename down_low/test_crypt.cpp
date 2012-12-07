#include "test_crypt.h"
using namespace std;

void test_crypt()
{
	char* entropy = NULL;
	rsa_key key;
	prng_state* random_gen;
	cout << "Start srng " <<  sprng_start(random_gen) << endl;
	cout << "srng state " <<  sprng_test() << endl;
	cout << "Rng done " << sprng_done(random_gen);
	//rng_make_prng(128, 0, state, NULL);
	//int num_rand = rng_gen_bytes(entropy, 64, NULL);
	//cout << "Got " << num_rand << "Bytes of entropy {" << entropy << "}\n";
}
