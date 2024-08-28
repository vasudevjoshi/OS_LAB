#!/bin/bash
echo "Enter n value"
read n
if [ $n == 0 ]; then
	echo "wrong input"
	exit 1
fi
f1=0
echo "The Fibonacci series is"
if [ $n == 1 ]; then 
	echo "$f1"
	exit 1
fi
f2=1
i=2
echo "$f1"
echo "$f2"
while [ $i -lt $n ]
	do
	f3=$((f1+f2))
	f1=$f2
	f2=$f3
	echo "$f3"
	i=$((i+1)); done
	

