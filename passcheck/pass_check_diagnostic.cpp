/*
*	Eugene Davis - November 2013 - CPE 412
*	Ithildin Password Cracker -- Pass Check Diagnostic
*
*/

/*
	This file is the simple diagnostic version of the pass check algorithm.
	It excutes significantly faster (at least an order of magnitude) than
	the MD5 version, and is less likely to be broken. It also "cheats"
	in many places, and so shoudn't be used for data collection.

	Unlike the MD5 version, it does not support user entered passwords/hashes
	and must be manually tweaked to test other passwords.
*/

#include "pass_check.h"
#include <stdio.h>
#include <stdlib.h>


const unsigned char real_pass[8] = {254, 'a', 's', 's', 'w', 'o', 'r', 'd'}; // Cheated here, since final will ALWAYS have the same number of outputs
const int real_length = 2;

/*
*
*	handleInput for serial version. Gets in the search size
*
*/
void handleInput(int argc, char *argv[], int *size)
{
	// Check that there are two arguments
	if (argc != 2)
	{
		printf("usage: ithildin_serial [search depth]\nMuch like in Moria, delving too deep may result in Balrogs\n");
		exit(1);
	}

	// Get size
	*size = atoi(argv[1]);
}


/*
*
*	handleInput for parallel version. Gets in the search size and the number of threads to set
*
*/
void handleInput(int argc, char *argv[], int *size, int *threads)
{
	// Check that there are three arguments
	if (argc != 3)
	{
		printf("usage: ithildin_parallel [search depth] [num threads]\nMuch like in Moria, delving too deep may result in Balrogs\n");
		exit(1);
	}

	// Get size
	*size = atoi(argv[1]);
	// Get number of threads
	*threads = atoi(argv[2]);
}

/*
*    int size:              size of password to check
*    unsigned char pass[]:  password to check
*    
*    Compares the current password guess against the correct password/hash
*/

bool check(int size, unsigned char pass[])
{
    if (size != real_length)
    {
        return false;
    }
    
    for (int i = 0; i < real_length; i++)
    {
        if (pass[i] != real_pass[i])
        {
            return false;
        }
    }
    return true;
}

