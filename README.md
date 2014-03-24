libmemchecker
=============

Set of C functions that can be used to generate logs for DMA function calls (malloc/calloc/realloc/free), thereby analyzing memory leak or other information.

All are written in C with supplement components written in Python or directly from GNU/Linux.

# GCC Wrapper Method

Directory: /1_Wl/

This memchecker makes use of the loader redirection features of `gcc`.

The example redirects malloc and free for demonstration.

## Known Issues

* Access to real DMA functions are not blocked.

# GCC Macro Method

Directory: /2_macro/

This method uses macro to redirect DMA function calls.

To redirect the memory (de)allocation functions, 
 - include the header memchecker.h.
 - compile with the libmemchecker.a library
 
The use of the library can be hidden by
 - hide the compile command by prepending the command with a @
 - echo a string as it if were the actual command

Notes
 * memchecker.c must not include memchecker.h to ensure access to the correct functions.
 * Makefile injects test.c with libmemchecker, adding the header inclusion, at compilation time so its use is transparent from students.
 * parser.py is a Python script to demonstration parsing the log file.

Todo:
 * write a C parser if needed.

# mtrace hook

Directory: /3_mtrace/

The third method uses mtrace component in Linux to generate and parse logs.

## Known Issues

1. Older versions of mtrace will treat realloc(ptr, 0) as __UNfreed__ memory (mtrace bug #14981 as recorded at https://sourceware.org/bugzilla/show_bug.cgi?id=14981).
	 * Update mtrace package to newest version.