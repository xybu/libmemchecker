#include <stdlib.h>
#include <stdio.h>

void * __mlib_malloc (size_t size) {
    void *lptr = malloc(size);
    printf("Malloc: %lu bytes @%p\n", size, lptr);
    return lptr;
}

void *__mlib_calloc(size_t nmemb, size_t size){
	void *lptr = calloc(nmemb, size);
	printf("Calloc: %lu bytes @%p\n", size * nmemb, lptr);
	return lptr;
}

void *__mlib_realloc(void *ptr, size_t size){
	void *lptr = realloc(ptr, size);
	printf("Realloc: %lu bytes from %p to %p\n", size, ptr, lptr);
	return lptr;
}

void __mlib_free(void * ptr) {
	printf("free: %p\n", ptr);
	free(ptr);
}

