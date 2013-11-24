#include <iostream>
#include "pass_check.h"

using namespace std;

int enumChars(int cur_pos, unsigned char pass[], int max_length);
void printPass(int length, unsigned char pass[]);

// Globals
const unsigned char start_char = 48; // character to start search at
const unsigned char end_char = 122; // character to end search at


int main()
{
	int max_length = 8;
    unsigned char *pass = new unsigned char[max_length];
   
    // Partition on starting letter to make partitions of even size 
    for (unsigned char i = start_char; i < end_char; i++)
    {
        cout << "Iteration " << i << endl;
        pass[0] = i;
        if (check(1, pass))
        {
            printPass(1, pass);
            return 0; // Hurray, we win
        }
        if (max_length != 1)
        {
            int length = enumChars(0, pass, max_length);
            if (-1 != length)
            {
                printPass(length, pass);
                return 0; // Hurray, we win                
            }
        }
    }
	return 0;
}

// Returns the size at which the password was found
int enumChars(int cur_pos, unsigned char pass[], const int max_length)
{
    cur_pos++; // Increment current position for this iteration of the recursion

    for (unsigned char i = start_char; i < end_char; i++)
    {
        pass[cur_pos] = i;

        // Success
        if (check(cur_pos + 1, pass))
        {
            return cur_pos + 1; // Return size of working password array
        }

        if (cur_pos + 1 != max_length)
        {
            int length = enumChars(cur_pos, pass, max_length); 
            if (-1 != length)
            {
                return length;
            }
        }
    }
    return -1;
}

void printPass(int length, unsigned char pass[])
{
	cout << "Success!" << endl;
    cout << "Password was ";
    for (int j = 0; j < length; j++)
    {   
    	cout << pass[j];
    }
    cout << endl;
}
