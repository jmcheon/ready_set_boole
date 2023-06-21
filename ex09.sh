#!/bin/bash

script_name=$(basename "$0")
exercise=$(basename "$0" .sh)
program="./rsb"

make all
if [ $# -eq 0 ]; then
	"$program" "$exercise" "A" "0,1" \
	&& "$program" "$exercise" "AB&" "0,1,2" "0,3,4" \
	&& "$program" "$exercise" "AB&" "0,1,2,3" "0,2,3,4" \
	&& "$program" "$exercise" "AB|" "0,1,2" "3,4,5" \
	&& "$program" "$exercise" "AB^" "1,2" "2,3" \
	&& "$program" "$exercise" "XY^" "1,2" "2,3" \
	&& "$program" "$exercise" "KM>" "1,2" "2,3" \
	&& "$program" "$exercise" "A" "0,1,2" \
	&& "$program" "$exercise" "OP=" "0,1,2" "3,4,5" \
	&& "$program" "$exercise" "AB|B&" "0,1" "1,2" \
	&& "$program" "$exercise" "AB|C&" "0,1,3" "3,4,5" "0,2,4" \
	&& "$program" "$exercise" "AB|C&D|" "0,1,3" "3,4,5" "0,2,4" \
	;
else
	#echo "Arguments provided: $@"
	"$program" "$exercise" $@
fi
