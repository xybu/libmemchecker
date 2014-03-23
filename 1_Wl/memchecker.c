#include <stdio.h>

void *__real_malloc (size_t);
void __real_free(void *);

/* This function wraps the real malloc */
void * __wrap_malloc (size_t size) {
    void *lptr = __real_malloc(size);
    printf("Malloc: %lu bytes @%p\n", size, lptr);
    return lptr;
}

void __wrap_free(void * ptr) {
	printf("free: %p\n", ptr);
	__real_free(ptr);
}
