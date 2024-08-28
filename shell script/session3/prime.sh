#!/bin/bash
echo "ENTER THE RANGE"
read n
echo "THE PRIME NUMBER UNIL THE RANGE $n IS:"
for((num=2;num<=n;num++)); do
	flag=1
	for((i=2;i<num;i++)); do
		if [ $((num % i)) == 0 ]; then
			flag=0
			break
		fi	
	
	done
	if [ $flag == 1 ]; then
		echo "$num"
		fi
done

