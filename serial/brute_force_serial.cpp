/*
*	Eugene Davis - November 2013 - CPE 412
*	Ithildin Password Cracker -- Serial Version
*
*/

/*
	To compile MD5:
		make

	To compile Diagnostic:
		make ithildin_diag

	To execute:
		ithildin_serial usage: ithildin_serial [md5sum] [search depth]
		Note that setting the search depth too deep may result in encountering Balrogs

	To execute Diagnostic:
		ithildin_parallel usage: ithildin_serial [search depth]
		Note that setting the search depth too deep may result in encountering Balrogs

	This program is designed to perform a depth-search search over a potential password
	space of all ASCII characters. It calculates the MD5 hash of each potential password
	and compares it to the user supplied hash. If it finds a password that results in
	the desired hash, it outputs the password to the user. If it fails, it alerts the
	user of the imminent Balrog and exits.

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
#ifdef csv
#include <fstream>
const char time_file[] = "times_serial.csv";
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
    for (unsigned char i = start_char; i < end_char; i++)
    {
        pass[0] = i;
		// Check if we got lucky on the first try
        if (check(1, pass))
        {
            printPass(1, pass);
            return 0; // Hurray, we win
        }
		// Make sure that we have a bigger than 1 max_length and should continue our search
        if (max_length >= 1)
        {
            int length = enumChars(0, pass, max_length);
			// If a positive value is returned, we have
			// a potential canidate! (One which will work
			// but in theory may just be a collision with
			// the original password) 
            if (-1 != length)
            {
                printPass(length, pass);
                return 0; // Hurray, we win                
            }
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
    cur_pos++; // Increment current position for this iteration of the recursion

    for (unsigned char i = start_char; i < end_char; i++)
    {
        pass[cur_pos] = i;

        // If check is successful
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

void printPass(int length, unsigned char pass[])
{
	TIMER_STOP;
	cout << "Password was ";
    for (int j = 0; j < length; j++)
    {   
    	cout << pass[j];
    }
    cout << endl;
#ifndef csv
	cout << "time=" << setprecision(8) <<  TIMER_ELAPSED/1000000.0 
        << " seconds" << endl;
#else
	// Write out time to a file of other runs of this version
	ofstream file(time_file, std::fstream::app);
	file << setprecision(8) <<  TIMER_ELAPSED/1000000.0 << ",";
	file.close();
#endif
}
