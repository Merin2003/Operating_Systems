 #!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: $0 <num1> <num2>"
    exit 1
fi

a=$1
b=$2

if [ $a -gt $b ]; then
   temp=$a
   a=$b
   b=$temp
fi

echo "Palindrome numbers between $a and $b:"

for ((i = a; i <= b; i++))
do
   n=$i
   r=0
   t=$i

   while [ $t -gt 0 ]
   do
