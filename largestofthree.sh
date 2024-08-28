#!/bin/bash

echo "Enter the three Numbers"
read n1
read n2
read n3

if [ $n1 -gt $n2 ];then
    large=$n1
else 
    large=$n2
fi
if [ $large -lt $n3 ];then
    large=$n3
fi
echo "the largest of three numbers $n1,$n2,$n3 is $large"