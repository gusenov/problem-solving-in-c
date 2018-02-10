#!/bin/bash

function test1 {
    gcc -Wall str.c -o str.out && ./str.out
}

function test2 {
    gcc -Wall str.c -o str.out
    echo -e "Hello, World!\nWw7 100500\n42" | ./str.out
}

clear
test1
