Eugene Davis - November 2013 - CPE 412
Ithildin Password Cracker -- README

Dependencies:
	OpenSSL
	OpenMP

To compile Ithildin on Linux with G++, run make
To compile Ithildin on UV with ICC, run make -f makefile_uv

dwarf_smith.sh will compile ALL versions of Ithildin automatically
under G++, and could easily be modified for UV

Per version running instructions are included in the source of
each version.

To automatically run the brute force version of Ithildin with
a randomly generate password of a set length, use dwarf_runner.sh

Example, for a password of 3 characters, search depth of 3 characters
and 6 threads:
bash dwarf_runner.sh 3 3 6
