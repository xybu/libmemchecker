#define _GNU_SOURCE

#include <dlfcn.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static int fd_out = 1;
static void *(*real_calloc)(size_t, size_t) = NULL;
static void *(*real_malloc)(size_t) = NULL;
static void *(*real_realloc)(size_t) = NULL;
static void (*real_free)(void *) = NULL;

void flushLog(){
	close(fd_out);
	sigset(SIGSTOP, SIG_DFL);
	sigset(SIGTSTP, SIG_DFL);
	_exit(0);
}

void flushLogWrapper(int x){
	flushLog();
}

int recordLog(char* format, ...) {
	char buf[1024] = {0};
	int bytesWritten = 0;
	
	if (format){
		va_list valist;
		va_start(valist, format);
		bytesWritten = vsnprintf(buf, 1024, format, valist);
		va_end(valist);
	}
	
	write(fd_out, buf, bytesWritten);
}

__attribute__((constructor)) void mallocCounter() {
	do {
		real_malloc = dlsym(RTLD_NEXT, "malloc");
		real_calloc = dlsym(RTLD_NEXT, "calloc");
		real_realloc = dlsym(RTLD_NEXT, "realloc");
		real_free = dlsym(RTLD_NEXT, "free");
	} while (!real_malloc || !real_calloc || !real_realloc || !real_free);
	
	fd_out = creat("libmemchecker_log.txt", 0664);
    
	sigset(SIGTSTP, flushLogWrapper);
    atexit(flushLog);
}

void *calloc(size_t nmemb, size_t size){
	void *lptr = real_calloc(nmemb, size);
	recordLog("+\t%lu\t%p\tcalloc\n", (long unsigned) size * nmemb, lptr);
	return lptr;
}

void *malloc(size_t size){
	void *lptr = real_malloc(size);
	recordLog("+\t%lu\t%p\tmalloc\n", (long unsigned) size, lptr);
	return lptr;
}

void *realloc(void *ptr, size_t size){
    void *lptr = real_realloc(ptr, size);
	fprintf(fd_output, "~\t%lu\t%p\t%p\trealloc\n", (long unsigned) size, ptr, lptr);
    return lptr;
}

void free(void *ptr){
    fprintf(fd_output, "-\t%p\n", ptr);
    real_free(ptr);
}
