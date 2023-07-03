#!/bin/bash

# define color codes
YELLOW="\033[0;38;5;220m"
GREEN="\033[0;38;5;42m"
RED="\033[0;38;5;196m"
BLUE="\033[0;38;5;21m"
PINK="\033[0;38;5;205m"
PURPLE="\033[0;38;5;93m"
ORANGE="\033[38;5;202m"
FIN="\033[0m"

script_name=$(basename "$0")
exercise=$(basename "$0" .sh)
program="./rsb"
output_file="output.txt"
print_table="false"

run_or_make() {
    local program="$1"
	local exercise="$2"
    local formula="$3"
	local print="$4"

    if command -v "$program" &>/dev/null; then
		if [ -n "$print" ]; then
    	    "$program" "$exercise" "$formula" "$print"
		elif [ -n "$formula" ]; then
    	    "$program" "$exercise" "$formula"
    	else
    	    "$program" "$exercise"
		fi
    else
        make all
    fi
}

if [ $# -eq 0 ]; then
	echo -e "Executing main examples.\n"
	echo -e "\tUsage: ./$script_name [formula] print"
	echo -e "\tUsage: ./$script_name [formula]"
	echo -e "\tUsage: ./$script_name test\n"
	run_or_make "$program" "$exercise"
elif [ $# -eq 1 ]; then
	#echo "Arguments provided: $1"
	if [ "$1" = "test" ]; then
    	formulas=(
    	    "A!B!&C!|"
    	    "A!B|C!&"
    	    "A!B|C!|D&"
    	    "A!B&C!|D&"
    	    "A!B&C!|D|"
    	    "A!B|C!&D|"
			)

    	for formula in "${formulas[@]}"; do
			echo ""
    	    echo "Running $program with equation: $formula"
    	    run_or_make "$program" "$exercise" "$formula" 
    	done
	else
		run_or_make "$program" "$exercise" "$1"
	fi
elif [ $# -eq 2 ]; then
	if [ "$2" = "print" ]; then
		run_or_make "$program" "$exercise" "$1" "$2" >> "$output_file"
		print_table="true"
	fi
else
	echo -e "Wrong number of arguments provided: $@\n"
	echo -e "\tUsage: ./$script_name [formula] print"
	echo -e "\tUsage: ./$script_name [formula]"
	echo -e "\tUsage: ./$script_name test\n"
fi


# print the result
if [ "$print_table" = "true" ]; then
    cat $output_file
    result=$(tail -n 1 "$output_file")

	echo -e "\nexecuting ex04 for formula: ${YELLOW}$1${FIN}"
	run_or_make "$program" "ex04" "$1"

	echo -e "\nexecuting ex04 for formula: ${YELLOW}$result${FIN}"
	run_or_make "$program" "ex04" "$result"

	rm "$output_file"
fi

