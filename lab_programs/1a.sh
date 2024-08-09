#!/bin/bash

echo "Enter the Number:"
read n
org=$n

while [ $n != 0 ]
do
	rem=$((n%10))
	rev=$((rev*10 +rem))
	n=$((n/10))
done
if [ $org == $rev ];then
	echo -n "Yes $org is palindrome"
else  
	echo -n "no $org is not palindrome"
fi

