#Write a shell program to find the largest of three numbers
#!/bin/bash
echo "Enter 3 numbers:"
read n1 n2 n3

if [ $n1 -gt $n2 ]; then 
	large=$n1
else 
	large=$n2
fi
if [ $large -lt $n3 ]; then
      large=$n3
fi
echo "The largest of three numbers $n1 ,$n2,$n3 is: $large"
