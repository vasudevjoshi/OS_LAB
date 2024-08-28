#!/bin/bash
echo "Enter 2 strings to be concatinated:"
read s1
read s2
res="${s1} ${s2}"
echo "NO of char=${#res}"
echo "Result=$res"
