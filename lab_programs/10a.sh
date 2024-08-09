#!/bin/bash

echo "Enter the range of the prime numbers :"
read n
echo "The prime numbers in the given range:"

for ((num=2; num<=n; num++)); do
    flag=1
    for ((i=2; i<num; i++)); do
        if [ $((num % i)) -eq 0 ]; then
            flag=0
            break
        fi
    done
    if [ $flag -eq 1 ]; then 
        echo "$num"
    fi
done
