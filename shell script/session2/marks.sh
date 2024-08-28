#!/bin/bash
echo "Enter marks"
read m
if [ $m -ge 90 ]; then
	echo "S"
elif [ $m -ge 60 ]; then
    echo "A"
elif [ $m -ge 40 ]; then
    echo "B"
else
	echo "FAIL"
fi
