#!/bin/bash

script_name=$(basename "$0")
exercise=$(basename "$0" .sh)
program="./rsb"

make all
if [ $# -eq 0 ]; then
	$program "$exercise" \
	&& "$program" "$exercise" 0 1 \
	&& "$program" "$exercise" 3 4 5 \
	&& "$program" "$exercise" 3 3 3 \
	;
else
	#echo "Arguments provided: $@"
	"$program" "$exercise" $@
fi
