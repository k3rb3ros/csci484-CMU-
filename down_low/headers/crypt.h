#include <iostream>
#include <stdio.h>
#include <tomcrypt.h>

using namespace std;

//important constants
#define ROUNDS 16
#define BLOCKSIZE 16

//important globals
unsigned char IV[BLOCKSIZE];
unsigned char KEY[BLOCKSIZE];
static int ERR = -1;
symmetric_OFB OFB;
symmetric_key TF_KEY;

int init_twofish(unsigned long int IV[], unsigned long int KEY[]);

int encrypt_twofish(unsigned long int* plain, unsigned long int* cipher);

int decrypt_twofish(unsigned long int* cipher, unsigned long int* plain);

void done();
