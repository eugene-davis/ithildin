# Eugene Davis - November 2013 - CPE 412
# Ithildin Password Cracker -- Serial Makefile

#A very minimal make file
# To compile and link the MD5 version, just type make
# To complie and link the diagnostic version (with simplier password logic, thus faster
# and less likely to get broken) type make ithildin_serial_diag
# Typing make clean will clean either version

#Linking
ithildin_serial: brute_force_serial.o pass_check.o
	g++ brute_force_serial.o pass_check.o -o ithildin_serial -lssl -lcrypto

ithildin_serial_diag: brute_force_serial.o pass_check_diagnostic.o
	g++ brute_force_serial.o pass_check_diagnostic.o -o brute_force_serial

#Compilation
pass_check.o: ../passcheck/pass_check.cpp
	g++ -c ../passcheck/pass_check.cpp -o pass_check.o -lssl -lcrypto

brute_force_serial.o: brute_force_serial.cpp
	g++ -c brute_force_serial.cpp -o brute_force_serial.o

pass_check_diagnostic.o: ../passcheck/pass_check_diagnostic.cpp
	g++ -c ../passcheck/pass_check_diagnostic.cpp -o pass_check_diagnostic.o

clean:
	rm *o ithildin_serial
