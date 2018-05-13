#!/bin/sh

#ls -1 | grep -e='*\.c' | xargs
gcc -c aux.c -o aux.o
gcc -c ui.c -o ui.o
gcc -c logic.c -o logic.o
gcc -c main.c -o main.o
gcc ui.o aux.o logic.o main.o -o huntSnake
