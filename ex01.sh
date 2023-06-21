#!/bin/bash

script_name=$(basename "$0")
exercise=$(basename "$0" .sh)
program="./rsb"

if [ $# -eq 0 ] || [ $# -eq 1 ]; then
	echo "Wrong number of arguments provided: $@"
	echo "Usage: ./$script_name [number1] [number2]"
else
	make all
	#echo "Arguments provided: $@"
	"$program" "$exercise" $1 $2
fi
