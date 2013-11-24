# Eugene Davis - November 2013 - CPE 412
# Ithildin Password Cracker -- Parallel Makefile

#A very minimal make file
# To compile and link the MD5 version, just type make
# To complie and link the diagnostic version (with simplier password logic, thus faster
# and less likely to get broken) type make ithildin_parallel_diag
# Typing make clean will clean either version

#Linking
ithildin_parallel: brute_force_parallel.o pass_check.o monte_carlo_parallel.o
	g++ brute_force_parallel.o pass_check.o -o ithildin_parallel -lssl -lcrypto -fopenmp
	g++ monte_carlo_parallel.o pass_check.o -o ithildin_mc_parallel -lssl -lcrypto -fopenmp

ithildin_parallel_diag: brute_force_parallel.o pass_check_diagnostic.o monte_carlo_parallel.o
	g++ brute_force_parallel.o pass_check_diagnostic.o -o ithildin_parallel -fopenmp
	g++ monte_carlo_parallel.o pass_check_diagnostic.o -o ithildin_mc_parallel -lssl -lcrypto -fopenmp

#Compilation
pass_check.o: ../passcheck/pass_check.cpp
	g++ -c ../passcheck/pass_check.cpp -o pass_check.o -lssl -lcrypto

brute_force_parallel.o: brute_force_parallel.cpp
	g++ -c brute_force_parallel.cpp -o brute_force_parallel.o -fopenmp

pass_check_diagnostic.o: ../passcheck/pass_check_diagnostic.cpp
	g++ -c ../passcheck/pass_check_diagnostic.cpp -o pass_check_diagnostic.o

monte_carlo_parallel.o: monte_carlo_parallel.cpp
	g++ -c monte_carlo_parallel.cpp -o monte_carlo_parallel.o

clean:
	rm *o ithildin_parallel ithildin_mc_parallel
