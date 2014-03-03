libmemchecker

author:	Xiangyu Bu
version: 1.0
last update: Mar 1, 2014

To redirect the memory (de)allocation functions, 
 - include the header memchecker.h.
 - compile with the libmemchecker.a library
 
The use of the library can be hidden by
 - hide the compile command by prepending the command with a @
 - echo a string as it if were the actual command

Notes
 * memchecker.c must not include memchecker.h to ensure access to the correct functions.
 * Makefile injects test.c with libmemchecker, adding the header inclusion, at compilation time so its use is transparent from students.
 * parser.c is a Python script to demonstration parsing the log file.

Todo:
 * write a C parser if needed.