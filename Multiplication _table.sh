#!/bin/bash

echo "enter the number"
read n

for((i=1;i<=10;i++))
do
     res=$((i*n))
     echo -e "$i * $n = $res"
done
