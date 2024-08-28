#!/bin/bash

	echo "Enter the prime Number Range: "
	read n
	echo "Prime Number in the range $n"
	for ((num=2; num<n;num++));do
		flag=1
		for ((i=2;i<num;i++));do
			if [ $((num%i)) -eq 0 ];then
				flag=0
				break
			fi
			done
			if [ $flag == 1 ];then
				echo "$num"
			fi
		done
