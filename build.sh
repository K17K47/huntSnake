#!/bin/sh

#ls -1 | grep -e='*\.c' | xargs
gcc -c aux.c -o aux.o
gcc -c ui.c -o ui.o
gcc -c logic.c -o logic.o
gcc -c menus.c -o menus.o
gcc -c main.c -o main.o
gcc ui.o aux.o logic.o menus.o main.o -o huntSnake
rm ui.o aux.o logic.o main.o menus.o
