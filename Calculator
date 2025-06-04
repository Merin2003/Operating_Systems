#!/bin/sh

echo "Calculator"
echo "1 - Addition"
echo "2 - Subtraction"
echo "3 - Multiplication"
echo "4 - Division"
echo "5 - Modulus"
echo "6 - Exit"

while true
do
    echo "Enter your choice: "
    read choice

    case $choice in
        1)
            echo "Enter two numbers: "
            read a b
            result=$((a + b))
            echo "Result: $result"
            ;;
        2)
            echo "Enter two numbers: "
            read a b
            result=$((a - b))
            echo "Result: $result"
            ;;
        3)
            echo "Enter two numbers: "
            read a b
            result=$((a * b))
            echo "Result: $result"
            ;;
        4)
            echo "Enter two numbers: "
            read a b
            if [ $b -ne 0 ]; then
                result=$((a / b))
                echo "Result: $result"
            else
                echo "Error: Division by zero is not allowed."
            fi
            ;;
        5)
            echo "Enter two numbers: "
            read a b
            result=$((a % b))
            echo "Result: $result"
            ;;
        6)
            echo "Exiting..."
            break
            ;;
        *)
            echo "Invalid choice. Please try again."
            ;;
    esac
done
