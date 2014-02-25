/**
 * 
 */

#ifndef _LIB_MEMCHECKER
#define _LIB_MEMCHECKER
#define malloc(x) __mlib_malloc(x)
#define calloc(x, y) __mlib_calloc(x, y)
#define realloc(x, y) __mlib_realloc(x, y)
#define free(x) __mlib_free(x)
#define strdup(x) __mlib_strdup(x)

extern void *__mlib_malloc(size_t size);
extern void *__mlib_calloc(size_t nmemb, size_t size);
extern void *__mlib_realloc(void *ptr, size_t size);
extern void __mlib_free(void *ptr);
extern void* __mlib_strdup(const char *ptr);
#endif
