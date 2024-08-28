#!/bin/bash

declare -A m1

echo "Enter the size of the array:"
read n
if [ $n == 0 ];then
	echo "enter valid number"
	exit
fi

for ((i=0; i<n;i++));do
	read m1[$i]
done

large=${m1[0]}

for((i=0;i<n;i++));do
	if [ ${m1[$i]} -gt $large ];then
		large=${m1[$i]}
	fi
done

echo "the large number is $large"
