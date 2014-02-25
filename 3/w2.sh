#!/bin/bash
gcc test.c
/usr/bin/env LD_PRELOAD=./libmalloccounter.so ./a.out
