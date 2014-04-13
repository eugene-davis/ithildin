/*
*	Eugene Davis - November 2013 - CPE 412
*	Ithildin Password Cracker -- Monte Carlo Parallel Version
*
*/

/*
	To compile MD5:
		make

	To compile Diagnostic:
		make ithildin_diag

	To execute:
		ithildin_mc_parallel usage: ithildin_serial [md5sum] [search depth] [num threads]
		Note that setting the search depth too deep may result in encountering Balrogs

	To execute Diagnostic:
		ithildin_mc_parallel usage: ithildin_serial [search depth] [num threads]
		Note that setting the search depth too deep may result in encountering Balrogs

	This program takes a Monte Carlo approach to password cracking, and does it in parallel.
	Because it must exceute ever iteration of the loop due to OpenMP (even once the condition
	is found) it is usually slower than the depth-first search done in other versions.

	Powered by Dwarves.
*/

#define csv

#include <iostream>
#include "../passcheck/pass_check.h"
#include <sys/time.h>
#include <iomanip>
#include <omp.h>
#include <openssl/rand.h>
#include <climits>
#ifdef csv
#include <fstream>
const char time_file[] = "times_mc_parallel.csv";
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

	// Parallel specific variables
	int threads;
	bool complete = false; // Check this flag to see if solution has been found
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

    // As in the serial version, make a very large number of iterations 
	#pragma omp parallel for schedule(guided)
    for (unsigned long i = 0; i < UINT_MAX; i++)
    {
		if (!complete) // If one thread gets a hit, it sets the complete flag
					   // and as a result all threads should rapidly terminate
		{
			unsigned char *pass = new unsigned char[max_length];
			unsigned char rand_size; // Get random number to pick the size to make
			// RAND_bytes outputs 0 if it doesn't have sufficient randomness, loop until it does
			// Made critical to ensure RAND_bytes has time to generate new randomness
			#pragma omp critical(rand_gen)
			while (RAND_bytes(&rand_size, 1) == 0);
			rand_size = rand_size % max_length;
			rand_size += 1; // Should never be 0

			// Again, loop until good entropy is output
			// Made critical to ensure RAND_bytes has time to generate new randomness
			#pragma omp critical(rand_gen)
			while (RAND_bytes(pass, rand_size) == 0);
			// Check if we got lucky
        	if (check(rand_size, pass))
        	{
            	complete = true;
				i = ULONG_MAX;
				password = pass;
				finalSize = rand_size;
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
		cout << "You shall not pass!" << endl;
	}
	TIMER_STOP;

#ifndef csv	
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

// Recursive function for enumerating all possible passwords for a given starting
// point (i.e. the first character passed to it by a for loop)
// Returns the size at which the password was found
int enumChars(int cur_pos, unsigned char pass[], const int max_length)
{
   // See brute_force_serial.cpp for this function
}

// Does as it says on the tin. Prints out the password that
// the program has discovered. Also prints out the elapsed time.
// Should only be called if program was successful.
void printPass(int length, unsigned char pass[])
{
   // See brute_force_serial.cpp for this function
}
