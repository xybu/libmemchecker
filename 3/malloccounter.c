#define _GNU_SOURCE

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SECRET_FD 17

static long counter = 0;

#define GET_REAL(f) do { \
    if (real_ ## f == NULL) { \
        real_ ## f = dlsym(RTLD_NEXT, #f); \
    } \
} while (0)

void printCount()
{
    char buf[1024];
    int sz;
    sz = sprintf(buf, "%ld\n", counter);
    sz = write(SECRET_FD, buf, sz);
    (void) sz;
}

__attribute__((constructor))
void mallocCounter()
{
    dup2(1, SECRET_FD);
    close(1);
    close(2);
    atexit(printCount);
}

void *calloc(size_t nmemb, size_t size)
{
    static void *(*real_calloc)(size_t, size_t) = NULL;
    counter++;
    GET_REAL(calloc);
    return real_calloc(nmemb, size);
}

void *malloc(size_t size)
{
    static void *(*real_malloc)(size_t) = NULL;
    counter++;
    GET_REAL(malloc);
    return real_malloc(size);
}

void free(void *ptr)
{
    static void (*real_free)(void *) = NULL;
    counter--;
    GET_REAL(free);
    real_free(ptr);
}
