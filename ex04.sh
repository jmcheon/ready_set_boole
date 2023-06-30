#!/bin/bash

script_name=$(basename "$0")
exercise=$(basename "$0" .sh)
program="./rsb"

run_or_make() {
    local program="$1"
	local exercise="$2"
    local formula="$3"
	local ordered="$4"

    if command -v "$program" &>/dev/null; then
		if [ -n "$formula" ] && [ -n "$ordered" ]; then
    	    "$program" "$exercise" "$formula" "$ordered"
		elif [ -n "$formula" ]; then
    	    "$program" "$exercise" "$formula"
		elif [ -n "$ordered" ]; then
    	    "$program" "$exercise" "$ordered"
    	else
    	    "$program" "$exercise" 
		fi
    else
        make all
    fi
}

if [ $# -eq 0 ]; then
	run_or_make "$program" "$exercise"
elif [ $# -eq 1 ]; then
	#echo "Arguments provided: $1"
	run_or_make "$program" "$exercise" "$1"
elif [ $# -eq 2 ]; then
	#echo "Arguments provided: $1"
	run_or_make "$program" "$exercise" "$1" "$2"
else
	echo "Wrong number of arguments provided: $@"
	echo "Usage: ./$script_name [formula] <ordered>"
fi
