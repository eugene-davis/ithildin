/*
*	Eugene Davis - November 2013 - CPE 412
*	Ithildin Password Cracker -- Pass Check Header
*
*/

// Checks if the character array passed to it is 
// the correct password
bool check(int size, unsigned char pass[]);

// Serial version of handleInput
void handleInput(int argc, char *argv[], int *size);

// Parallel version of handleInput
void handleInput(int argc, char *argv[], int *size, int *threads);
