##############################################################
# Eugene Davis - November 2013 - CPE 412
# Ithildin Password Cracker -- Dwarf Runner
# Generates a random password, makes its MD5, then runs
# both the serial and parallel versions of the program with
# the MD5 it made.
##############################################################

# usage: bash dwarf_runner.sh [password size] [search depth] [num threads]

# /bin/bash

#Check arguments
if [ -z "$1" ] || [ -z "$2" ] || [ -z "$3" ]; then
	echo "usage: bash dwarf_runner.sh [password size] [search depth] [num threads]"
	exit
fi

# Generate password in base64 - covers much of the 
# character set used
pass=`openssl rand -base64 $1 | cut -c1-$1`
# Generate the MD5 sum of the generated password
md5=`echo -n $pass | md5sum | cut -c1-32`


echo "Calling Ithildin with original password of $pass"
echo

echo "Launching serial version"
cd serial 
./ithildin_serial $md5 $2

cd ..

echo
echo
echo "Launching parallel version"
cd parallel
./ithildin_parallel $md5 $2 $3

# Reset directory location
cd ..
