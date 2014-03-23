#!/bin/bash
/usr/bin/env MALLOC_TRACE=./log.txt ./a.out
mtrace a.out log.txt

