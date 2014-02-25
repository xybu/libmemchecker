#!/bin/bash
gcc -O2 -g -std=c99 -shared -fPIC malloccounter.c -ldl -o libmalloccounter.so
gcc -O2 -g -std=c99 -c list.c -o list.o
gcc -O2 -g -std=c99 -c list_caller.c -o list_caller.o
gcc -O2 -g -std=c99  list.o list_caller.o -o testlist
/usr/bin/env LD_PRELOAD=./libmalloccounter.so ./testlist $1
