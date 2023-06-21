#!/bin/bash

script_name=$(basename "$0")
exercise=$(basename "$0" .sh)
program="./rsb"

make all
if [ $# -eq 0 ]; then
	"$program" "$exercise"
else
	#echo "Arguments provided: $@"
	"$program" "$exercise" $1
fi
