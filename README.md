libmemchecker
=============

* Contact: [@xybu92](http://xybu.me)
* Last Update: Mar 24, 2014

Set of C functions that can be used to generate logs for DMA function calls (malloc/calloc/realloc/free), thereby analyzing memory leak or other information.

All the components are written so as to be suitable for tasks like automated testing (especially if the tested program runs a jail) where valgrind and other
widely used tools may be too slow to use or have other restrictions.

All are written in C with supplement components written in Python or directly from GNU/Linux.

Note:
 * _The test driver should check against abnormal termination of programs caused by say, segmentation fault, before performing memcheck functions._
 * Never assume the tested program to behave the way you want.

# GCC Wrapper Method

Directory: /1_Wl/

This memchecker makes use of the loader redirection features of `gcc`.

The example redirects only `malloc` and `free` for demonstration.

## Known Issues

* Access to real DMA functions are not blocked.

# GCC Macro Method

Directory: /2_macro/

This method uses macro to redirect DMA function calls.

## Usage
* To redirect the memory (de)allocation functions, 
	 - include the header `memchecker.h`.
	 - compile with the `libmemchecker.a` library (See `Makefile`)
* The use of the library can be hidden by
	 - hiding the compile command by pre-pending the command with a `@`
	 - `echo`ing a string as it if were the actual command

## Notes
 * `memchecker.c` must not include `memchecker.h` to ensure access to the actual functions.
 * `Makefile` injects tested program `test.c` with `libmemchecker`, adding the header inclusion, at compilation time so its use is hidden.
 * `parser.py` is a Python script to demonstration parsing the log file.

## Todo
 * write a C parser if needed.

# mtrace hook

Directory: /3_mtrace/

The third method uses `mtrace` component in Linux to generate and parse logs.

## Usage

* Simply compile the program with the `mtrace_hook`, when program exits a mtrace log will be generated
* Issue `mtrace` command to analyze the log (see the commands in `wrapper.sh`).
	 * When there is no memory leak, `mtrace` will return `No Memory Leaks`
	 * Otherwise a list of addresses, sizees, and callers will be printed
	 * Refer to http://en.wikipedia.org/wiki/Mtrace

## Known Issues

1. Older versions of mtrace will treat realloc(ptr, 0) as __UNfreed__ memory (mtrace bug #14981 as recorded at https://sourceware.org/bugzilla/show_bug.cgi?id=14981).
	 * Update mtrace package to newest version.
