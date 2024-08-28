#!/bin/bash
declare -A m1
declare -A m2
echo "Enter matrix 1 elements"
for((i=0;i<3;i++));do
	for((j=0;j<3;j++));do
		read m1[$i,$j]
	done
done
echo "Enter matrix 2 elements"
for((i=0;i<3;i++));do
	for((j=0;j<3;j++));do
		read m2[$i,$j]
	done
done
echo "MATRIX SUM:"
for((i=0;i<3;i++));do
	for((j=0;j<3;j++));do
	echo -n  "$((${m1[$i,$j]} + ${m2[$i,$j]})) "
	done
	echo
done


