#! /bin/bash

# Generates and runs the different runs of Ithildin on UV

# Array of MD5 sums for each depth
md5[1]="83878c91171338902e0fe0fb97a8c47a" # p
md5[2]="e36314e624d2b2ca257e1f1ecb381f93" # 2a
md5[3]="4ee955413ea0bd37382a10edd6939d5f" # ABQ
md5[4]="24f7708fabd2f0dc4e2351b36843dd3e" # @H4
md5[5]="07a7f5f2f4a71eb862bc470ea0c4d16e" # !a2C

# Generate 4 sizes of password
for i in 1 2 3 4
do	
	# Generate 5 runs worth of passwords
	for j in 1 2 3 4 5
	do
		pass=`openssl rand -base64 $i | cut -c1-$i`
		# Generate the MD5 sum of the generated password
		md5[$i*$j]=`echo -n $pass | md5sum | cut -c1-32`
	done
done


# Create serial structure
run_cat="serial_run"
mkdir -p "$run_cat"

for i in 1 2 3 4
do
	cur_dir="$run_cat/depth_$i"
	mkdir -p $cur_dir
	cp -r "serial" "passcheck" $cur_dir
	cd "$cur_dir/serial"
	mv makefile_uv makefile
	make
	rm *o
	
	# Generate 5 scripts to run
	for j in 1 2 3 4 5
	do
		filename="${run_cat}_$j.scr"
		cur_md5=${md5[$i*$j]}
		command="ithildin_serial ${cur_md5} $i"
		echo "#!/bin/bash" >> $filename
        echo "./$command" >> $filename
	done

	# Generate inputs file
	echo "class" >> inputs.txt # Queue name
	echo 1 >> inputs.txt # Number of processors
	echo >> inputs.txt # Accept default
	echo >> inputs.txt # Accept default
	echo "uv" >> inputs.txt # Machine to run on

	bash run_scripts.sh

	cd ../../..
done

# Create parallel structure
# First by number of threads
for k in 2 4 8
do

	run_cat="parallel_run_$k"
	mkdir -p "$run_cat"

	for i in 1 2 3 4
	do
		cur_dir="$run_cat/depth_$i"
		mkdir -p $cur_dir
		cp -r "parallel" "passcheck" $cur_dir
		cd "$cur_dir/parallel"
		mv makefile_uv makefile
		make
		rm *o
	
		# Generate 5 scripts to run
		for j in 1 2 3 4 5
		do
			filename="${run_cat}_$i_$j.scr"
			cur_md5=${md5[$i*$j]}
			command="ithildin_parallel ${cur_md5} $i $k"
			echo "#!/bin/bash" >> $filename
		    echo "./$command" >> $filename
		done

		# Generate inputs file
		echo "class" >> inputs.txt # Queue name
		echo $k >> inputs.txt # Number of processors
		echo >> inputs.txt # Accept default
		echo >> inputs.txt # Accept default
		echo "uv" >> inputs.txt # Machine to run on

		bash run_scripts.sh

		cd ../../..
	done

done
