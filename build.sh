#!/bin/bash
cd list
gcc list.c -fpic -c
gcc -shared -o liblist.so list.o
cd ..

cd delta_list
gcc delta_list.c -I ../list/ -fpic -c
gcc -shared -o libdelta_list.so delta_list.o
cd ..

gcc -I list/ -I delta_list/ -L list/ -L delta_list/ main.c -l list -l delta_list -o main.o