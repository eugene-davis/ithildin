Eugene Davis - November 2013 - CPE 412
Ithildin Password Cracker -- README

Ithildin is a simplistic (and mediocre) password cracker made parallel with OpenMP. Though it doesn't hold up against most password crackers out there, it appears to be the only one themed around Lord of the Rings.

For those unfamiliar with ithildin from Lord of the Rings, it is the substance used on the Doors of Durin to provide a hint to their password (http://tolkiengateway.net/wiki/Ithildin).

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
