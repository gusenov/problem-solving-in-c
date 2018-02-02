#!/bin/bash

gcc -Wall text.c -o text.out

function run() {
    hexdump -C "data.$1" > data.hex
    
    hexdump -C "tofind.$1" > tofind.hex
    
    hexdump -C "replacedata.$1" > replacedata.hex
    
    ../text.out -i data.$1 tofind.$1 replacedata.$1 -o output.$1
    hexdump -C "output.$1" > output.hex
    diff -s "data.$1" "output.$1"
}

function rdmrun() {
    rm *.*
    
    sleep 1
    ../text.out -g data.bin -s $1
    
    sleep 1
    ../text.out -g tofind.bin -s $2
    
    
    sleep 1
    ../text.out -g replacedata.bin -s $3
        
    diff -s tofind.bin replacedata.bin
    
    run "bin"
}

#cd test1
#echo -e "\nTest 1\nDir: $(pwd)"
#rdmrun 10 1 1
#cd ..

#cd test2
#echo -e "\nTest 2\nDir: $(pwd)"
#rdmrun 100 1 3
#cd ..

#cd test3
#echo -e "\nTest 3\nDir: $(pwd)"
#run "txt"
#cd ..

cd test4
echo -e "\nTest 4\nDir: $(pwd)"
run "txt"
cd ..

echo ""
