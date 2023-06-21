#!/bin/bash

script_name=$(basename "$0")
exercise=$(basename "$0" .sh)
program="./rsb"

run_or_make() {
    local program="$1"
	local exercise="$2"
    local formula="$3"

    if command -v "$program" &>/dev/null; then
		if [ -n "$formula" ]; then
    	    "$program" "$exercise" "$formula"
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
else
	echo "Wrong number of arguments provided: $@"
	echo "Usage: ./$script_name ['formula']"
fi
