/*
*
* Pass Check Diaganostic exists as a simplier password checker than the MD5 sum
* and can be used to test if the problem is occurring in the main body of the
* code or in the password checker.
*
*/

#include "pass_check.h"
#include <stdio.h>


const unsigned char real_pass[8] = {49, 49, 120, 121, 100, 100, 67, 88}; // Cheated here, since final will ALWAYS have the same number of outputs
const int real_length = 3;

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

