/**
 * libmemchecker v1.0
 * 
 * The second implementation of libmemchecker
 * @author	Xiangyu Bu
 * @date	Mar 1, 2014
 */
#ifndef _LIB_MEMCHECKER
#include <stddef.h>
#define _LIB_MEMCHECKER

#ifdef malloc
	#undef malloc
#endif
#define malloc __mlib_malloc

#ifdef calloc
	#undef calloc
#endif
#define calloc __mlib_calloc

#ifdef realloc
	#undef realloc
#endif
#define realloc __mlib_realloc

#ifdef free
	#undef free
#endif
#define free __mlib_free

#ifdef strdup
	#undef strdup
#endif
#define strdup __mlib_strdup

extern void *__mlib_malloc(size_t size);
extern void *__mlib_calloc(size_t nmemb, size_t size);
extern void *__mlib_realloc(void *ptr, size_t size);
extern void __mlib_free(void *ptr);
extern char* __mlib_strdup(const char *ptr);

#endif
