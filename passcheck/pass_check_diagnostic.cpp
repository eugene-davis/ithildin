/*
*
* Pass Check Diaganostic exists as a simplier password checker than the MD5 sum
* and can be used to test if the problem is occurring in the main body of the
* code or in the password checker.
*
*/

#include "pass_check.h"
#include <stdio.h>
#include <stdlib.h>


const unsigned char real_pass[8] = {'p', 'a', 's', 's', 'w', 'o', 'r', 'd'}; // Cheated here, since final will ALWAYS have the same number of outputs
const int real_length = 4;

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
		printf("usage: brute_force_serial [max length]\n");
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
		printf("usage: brute_force_parallel [max length] [num threads]\n");
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

