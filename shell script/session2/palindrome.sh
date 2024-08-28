#!/bin/bash
echo "enter number"
read n
org=$n
while [ $n != 0 ]
	do
		rem=$((n%10))
		rev=$((rev*10+rem))
		n=$((n/10))
		
	done
if [ $org == $rev ]; then
	echo -n "YES"
	echo  " PALINDROME"
else
	echo -n "NO"
	echo " NOT PALINDROME"
fi

