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

inline int enumChars(int cur_pos, unsigned char pass[], int max_length);
inline void printPass(int length, unsigned char pass[]);

// Globals
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
		if (!complete) // If complete, should go quite a bit faster
		{
        	//cout << "Iteration " << i << endl;
			unsigned char *pass = new unsigned char[max_length];
        	pass[0] = i;
        	if (check(1, pass))
        	{
				password = pass;
				finalSize = 1;
				complete = true;
        	}
        	if (max_length != 1)
        	{
            	int length = enumChars(0, pass, max_length);
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
	TIMER_STOP;

	cout << "time=" << setprecision(8) <<  TIMER_ELAPSED/1000000.0 
        << " seconds" << endl;
	
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
	TIMER_STOP;
	cout << "time=" << setprecision(8) <<  TIMER_ELAPSED/1000000.0 
        << " seconds" << endl;

	cout << "Success!" << endl;
    cout << "Password was ";
    for (int j = 0; j < length; j++)
    {   
    	cout << pass[j];
    }
    cout << endl;
}
