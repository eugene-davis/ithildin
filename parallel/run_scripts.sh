#!/bin/bash

for file in *scr
do
	chmod 744 $file
	run_script $file < inputs.txt
done
