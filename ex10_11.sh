#!/bin/bash

script_name=$(basename "$0")
exercise="ex10"
program="./rsb"

make all
if [ $# -eq 0 ]; then
	"$program" "$exercise" "0" "0" \
	&& "$program" "$exercise" "0" "1" \
	&& "$program" "$exercise" "57" "2234" \
	&& "$program" "$exercise" "0" "65535" \
	&& "$program" "$exercise" "65535" "65535" \
	&& "$program" "$exercise" "65535" "0" \
	&& "$program" "$exercise" "6553" "2345" \
	;
elif [ $# -eq 2 ]; then
	"$program" "$exercise" "$1" "$2"
else
	#echo "Arguments provided: $@"
	"$program" "$exercise" $@
fi
