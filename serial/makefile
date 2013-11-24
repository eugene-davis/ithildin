#Linking
brute_force_serial: brute_force_serial.o pass_check.o
	g++ brute_force_serial.o pass_check.o -o brute_force_serial -lssl -lcrypto

brute_force_serial_diag: brute_force_serial.o pass_check_diagnostic.o
	g++ brute_force_serial.o pass_check_diagnostic.o -o brute_force_serial

#Compilation
pass_check.o: ../passcheck/pass_check.cpp
	g++ -c ../passcheck/pass_check.cpp -o pass_check.o -lssl -lcrypto

brute_force_serial.o: brute_force_serial.cpp
	g++ -c brute_force_serial.cpp -o brute_force_serial.o

pass_check_diagnostic.o: ../passcheck/pass_check_diagnostic.cpp
	g++ -c ../passcheck/pass_check_diagnostic.cpp -o pass_check_diagnostic.o

clean:
	rm *o brute_force_serial
