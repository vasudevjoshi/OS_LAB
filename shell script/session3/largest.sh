#!/bin/bash
arr=( 12 32 34 45 534 23 )
max=${arr[0]}
for (( i=0; i<6; i++ )); do
	if [ ${arr[$i]} -gt $max ]; then
		max=${arr[$i]}
	fi
	done
	echo 'THE LARGEST ELEMENT IS :' $max
