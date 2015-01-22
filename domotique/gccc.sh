#!/bin/bash

echo "compile and link ihome start"

echo "compiling..."
gcc -std=c99 -c ihome_*.c

echo "linking..."
gcc -o iHome_Start ihome*.o -lbcm2835 -lpthread
