#!/bin/bash

#gcc -Wall pages.c -o pages.out && ./pages.out

gcc -Wall pages.c -o pages.out
cat input.txt | ./pages.out

