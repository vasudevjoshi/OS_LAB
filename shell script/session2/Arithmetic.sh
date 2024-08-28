#!/bin/bash

echo "ENTER TWO NUMBERS"
read n1
read n2
echo "ENTER THE OPERATION:"
echo "ADD SUB MUL REM QUO"
read choice
case "$choice" in 
"ADD")
echo "$((n1+n2))"
;;
"SUB")
echo "$((n1-n2))"
;;
"MUL")
echo "$((n1*n2))"
;;
"REM")
echo "$((n1%n2))"
;;
"QUO")
echo "$((n1/n2))"
;;
*)
echo "ENTER CORRECT OPTION"
;;
esac
