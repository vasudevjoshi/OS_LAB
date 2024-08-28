#!/bin/bash

echo "ENTER FILE NAME"
read f
if [ -f "$f" ]; then
	echo "FOUND"
else 
	echo "NOT FOUND"
fi

