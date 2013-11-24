/*
*	Eugene Davis - November 2013 - CPE 412
*	Ithildin Password Cracker -- Parallel Version
*
*/

/*
	To compile MD5:
		make

	To compile Diagnostic:
		make ithildin_diag

	To execute:
		ithildin_parallel usage: ithildin_serial [md5sum] [search depth] [num threads]
		Note that setting the search depth too deep may result in encountering Balrogs

	To execute Diagnostic:
		ithildin_parallel usage: ithildin_serial [search depth] [num threads]
		Note that setting the search depth too deep may result in encountering Balrogs

	This program is designed to perform a depth-search search over a potential password
	space of all ASCII characters. It calculates the MD5 hash of each potential password
	and compares it to the user supplied hash. If it finds a password that results in
	the desired hash, it outputs the password to the user. If it fails, it alerts the
	user of the imminent Balrog and exits.

	It utilizes OpenMP to split the for loop that provides the initial set of characters
	into different threads, dramatically improving execution time.

	Powered by Dwarves.
*/

#include <iostream>
#include "../passcheck/pass_check.h"
#include <sys/time.h>
#include <iomanip>
#include <omp.h>

using namespace std;

/* copied from mpbench */
#define TIMER_CLEAR     (tv1.tv_sec = tv1.tv_usec = tv2.tv_sec = tv2.tv_usec = 0)
#define TIMER_START     gettimeofday(&tv1, (struct timezone*)0)
#define TIMER_ELAPSED   ((tv2.tv_usec-tv1.tv_usec)+((tv2.tv_sec-tv1.tv_sec)*1000000))
#define TIMER_STOP      gettimeofday(&tv2, (struct timezone*)0)
struct timeval tv1,tv2;

int enumChars(int cur_pos, unsigned char pass[], int max_length);
void printPass(int length, unsigned char pass[]);

// Globals for the starting and ending characters for each iteration of the
// search to go through
const unsigned char start_char = 0; // character to start search at
const unsigned char end_char = 255; // character to end search at


int main(int argc, char *argv[])
{
	

	int max_length;

	// Parallel specific variables
	int threads;
	volatile bool complete = false; // Check this flag to see if solution has been found
	int finalSize = 0; // Final size of password
	unsigned char *password; // Final password

	// Use input then set the number of threads
	handleInput(argc, argv, &max_length, &threads);
	omp_set_num_threads(threads);
   
	/*
   Start recording the execution time
   */
   TIMER_CLEAR;
   TIMER_START;
    // Partition on starting letter to make partitions of even size 
	#pragma omp parallel for schedule(guided)
    for (unsigned char i = start_char; i < end_char; i++)
    {
		if (!complete) // If one thread gets a hit, it sets the complete flag
					   // and as a result all threads should rapidly terminate
		{
        	// Set up a character array local to each thread
			unsigned char *pass = new unsigned char[max_length];
        	pass[0] = i;

			// Check if the single character in this iteration is the password
        	if (check(1, pass))
        	{
				password = pass;
				finalSize = 1;
				complete = true;
        	}
			// Check that the maximum length is more than 1
        	if (max_length >= 1)
        	{
            	int length = enumChars(0, pass, max_length);
				// If a positive value is returned, we have
				// a potential canidate! (One which will work
				// but in theory may just be a collision with
				// the original password)
            	if (-1 != length)
            	{
					password = pass;
					finalSize = length;
					complete = true;                
            	}
        	}
		}
    }
	if (complete)
	{
		printPass(finalSize, password);
	}
	// Failure! Even the Orcs are running away now.
	else
	{
		cout << "A Balrog ate your password." << endl;
	}
	TIMER_STOP;

	cout << "time=" << setprecision(8) <<  TIMER_ELAPSED/1000000.0 
        << " seconds" << endl;
	
	return 0;
}

// Recursive function for enumerating all possible passwords for a given starting
// point (i.e. the first character passed to it by a for loop)
// Returns the size at which the password was found
int enumChars(int cur_pos, unsigned char pass[], const int max_length)
{
    cur_pos++; // Increment current position for this iteration of the recursion
	// Iterate through all characters
    for (unsigned char i = start_char; i < end_char; i++)
    {
        pass[cur_pos] = i;

        // If check is succesful
        if (check(cur_pos + 1, pass))
        {
            return cur_pos + 1; // Return size of working password array
        }
		// If check is not successful, keep digging
        if (cur_pos + 1 < max_length)
        {
			// Recursion happening right here
            int length = enumChars(cur_pos, pass, max_length); 
            if (-1 != length)
            {
                return length;
            }
        }
    }
    return -1;
}

// Does as it says on the tin. Prints out the password that
// the program has discovered. Also prints out the elapsed time.
// Should only be called if program was successful.
void printPass(int length, unsigned char pass[])
{
	cout << "Mithril!" << endl;
    cout << "Password was ";
    for (int j = 0; j < length; j++)
    {   
    	cout << pass[j];
    }
    cout << endl;
}
