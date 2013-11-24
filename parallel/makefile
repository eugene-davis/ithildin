#Linking
brute_force_parallel: brute_force_parallel.o pass_check.o
	g++ brute_force_parallel.o pass_check.o -o brute_force_parallel -lssl -lcrypto -fopenmp

brute_force_parallel_diag: brute_force_parallel.o pass_check_diagnostic.o
	g++ brute_force_parallel.o pass_check_diagnostic.o -o brute_force_parallel -fopenmp

#Compilation
pass_check.o: ../passcheck/pass_check.cpp
	g++ -c ../passcheck/pass_check.cpp -o pass_check.o -lssl -lcrypto

brute_force_parallel.o: brute_force_parallel.cpp
	g++ -c brute_force_parallel.cpp -o brute_force_parallel.o -fopenmp

pass_check_diagnostic.o: ../passcheck/pass_check_diagnostic.cpp
	g++ -c ../passcheck/pass_check_diagnostic.cpp -o pass_check_diagnostic.o

clean:
	rm *o brute_force_parallel
