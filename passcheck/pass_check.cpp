#include "pass_check.h"
#include <openssl/md5.h>
#include <stdio.h>
#include <stdlib.h>

const int MD5_HEX_LENGTH = 33;
//char md5[MD5_HEX_LENGTH] = "0cc175b9c0f1b6a831c399e269772661"; // a
//char md5[MD5_HEX_LENGTH] = "187ef4436122d1cc2f40dc2b92f0eba0"; // ab
char md5[MD5_HEX_LENGTH];// = "4141638976566cb8526c738e7514df9f"; //ya1
//char md5[MD5_HEX_LENGTH] = "286755fad04869ca523320acce0dc6a4"; //password

/*
*
*	handleInput for serial version. Gets in the MD5 array, and the search size
*
*/
void handleInput(int argc, char *argv[], int *size)
{
	// Check that there are three arguments and the in the MD5 sum argument
	// is a null terminated 32 char string
	if (argc != 3 || argv[1][MD5_HEX_LENGTH + 1] != '\0')
	{
		printf("usage: brute_force_serial [md5sum] [max length]\n");
		exit(1);
	}
	// Copy over MD5 sum
	for (int i = 0; i < MD5_HEX_LENGTH; i++)
	{
		md5[i] = argv[1][i];
	}

	// Get size
	*size = atoi(argv[2]);
}


/*
*
*	handleInput for parallel version. Gets in the MD5 array, the search size, and the number of threads to set
*
*/
void handleInput(int argc, char *argv[], int *size, int *threads)
{
	// Check that there are three arguments and the in the MD5 sum argument
	// is a null terminated 32 char string
	if (argc != 4 || argv[1][MD5_HEX_LENGTH + 1] != '\0')
	{
		printf("usage: brute_force_parallel [md5sum] [max length] [num threads]\n");
		exit(1);
	}
	// Copy over MD5 sum
	for (int i = 0; i < MD5_HEX_LENGTH; i++)
	{
		md5[i] = argv[1][i];
	}

	// Get size
	*size = atoi(argv[2]);
	// Get number of threads
	*threads = atoi(argv[3]);
}

/*
*    int size:              size of password to check
*    unsigned char pass[]:  password to check
*    
*    Compares the current password guess against the correct password/hash
*/
bool check(int size, unsigned char pass[])
{
	unsigned char result[MD5_DIGEST_LENGTH];
    char buffer[MD5_HEX_LENGTH];
    char final_result[MD5_HEX_LENGTH];

    // Because of the library's expected input, the *& cancellation is required
    MD5((unsigned char*) pass, size, (unsigned char*) &result);
    
    int i, j;
    for (i = 0, j = 0; i < MD5_DIGEST_LENGTH; i++, j += 2)
    {
        sprintf(buffer, "%02x", result[i]);
        final_result[j] = buffer[0];
        final_result[j + 1] = buffer[1];
    }

    for (int i = 0; i < 32; i++)
    {
        if (md5[i] != final_result[i])
        {
            return false;
        }
    }
    return true;
}

