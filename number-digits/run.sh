#!/bin/bash

#gcc -Wall digits.c -o digits.out -lm && ./digits.out

gcc -Wall digits.c -o digits.out -lm
echo "-24012018" | ./digits.out
