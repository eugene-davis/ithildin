##############################################################
# Eugene Davis - November 2013 - CPE 412
# Ithildin Password Cracker -- Dwarf Smith
# Updates/Initially compiles both serial and parallel versions
# of Ithildin
##############################################################

# usage: bash dwarf_smith.sh
# Diagnostic version must be manually compiled

# /bin/bash

echo "Cleaning and compiling serial version"
cd serial
make clean
make

cd ..

echo "Cleaning and compiling parallel version"
cd parallel
make clean
make
