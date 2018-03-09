#!/bin/bash

clear
gcc -Wall replace-symbolic-constants.c -o replace-symbolic-constants.out
#echo -e "1024\naaa'6'xxx" | ./replace-symbolic-constants.out
#echo "1024 aaa6xxx" | ./replace-symbolic-constants.out
./replace-symbolic-constants.out
