/*
*	Eugene Davis - November 2013 - CPE 412
*	Ithildin Password Cracker -- Monte Carlo Version
*
*/

/*
	To compile MD5:
		make

	To compile Diagnostic:
		make ithildin_diag

	To execute:
		ithildin_mc_serial usage: ithildin_serial [md5sum] [search depth]
		Note that setting the search depth too deep may result in encountering Balrogs

	To execute Diagnostic:
		ithildin_mc_parallel usage: ithildin_serial [search depth]
		Note that setting the search depth too deep may result in encountering Balrogs

	This version of Ithildin randomoly guesses at potential passwords. In theory it should
	average out to about the same execution time as a depth-first search, given enough
	runs over a large enough data set.

	This version of Ithildin is serial, and exists to allow a comparison to the parallel
	version.

	Powered by Dwarves.
*/

// Enable to write output to files
#define csv

#include <iostream>
#include "../passcheck/pass_check.h"
#include <sys/time.h>
#include <iomanip>
#include <openssl/rand.h>
#include <climits>
#ifdef csv
#include <fstream>
const char time_file[] = "times_mc_serial.csv";
#endif

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
	
	// Get geared up for input
	handleInput(argc, argv, &max_length);

	// Unlike in the parallel version, we only need a single array
	// Non-valid guesses just get overwritten
    unsigned char *pass = new unsigned char[max_length];
   
	/*
   Start recording the execution time
   */
   TIMER_CLEAR;
   TIMER_START;
	// Just repeat for the max value of unsigned int, if still can't find it give up
    for (unsigned int i = 0; i < UINT_MAX; i++)
    {
		unsigned char rand_size; // Get random number to pick the size to make
		// RAND_bytes outputs 0 if it doesn't have sufficient randomness, loop until it does
		while (RAND_bytes(&rand_size, 1) == 0);
		rand_size = rand_size % max_length;
		rand_size += 1; // Should never be 0

		// Again, loop until good entropy is output
		while (RAND_bytes(pass, rand_size) == 0);
		// Check if we got lucky
        if (check(rand_size, pass))
        {
            printPass(rand_size, pass);
            return 0; // Hurray, we win
        }
    }
	// Failure! Even the Orcs are running away now.
	TIMER_STOP;
#ifndef csv	
	cout << "You shall not pass! Serial Run." << endl;
	cout << "time=" << setprecision(8) <<  TIMER_ELAPSED/1000000.0 
        << " seconds" << endl;
#else
	// Write out time to a file of other runs of this version
	ofstream file(time_file, std::fstream::app);
	file << setprecision(8) <<  TIMER_ELAPSED/1000000.0 << ",";
	file.close();
#endif
	
	return 0;
}

// Returns the size at which the password was found
int enumChars(int cur_pos, unsigned char pass[], const int max_length)
{
   // See brute_force_serial.cpp for this function
}

void printPass(int length, unsigned char pass[])
{
	// See brute_force_serial.cpp for this function
}
