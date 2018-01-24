#!/bin/bash

#gcc -Wall words.c -o words.out && ./words.out

gcc -Wall words.c -o words.out
echo "Stars can't shine without darkness." | ./words.out
