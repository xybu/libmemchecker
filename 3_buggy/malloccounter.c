#define _GNU_SOURCE
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dlfcn.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

static int fd_out = 1;
static FILE* fd_output = NULL;

static void *(*real_calloc)(size_t, size_t) = NULL;
static void *(*real_malloc)(size_t) = NULL;
static void *(*real_realloc)(void *, size_t) = NULL;
static void (*real_free)(void *) = NULL;

void flushLog(){
	//fclose(fd_output);
	//sigset(SIGSTOP, SIG_DFL);
	//sigset(SIGTSTP, SIG_DFL);
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
	
	fprintf(stderr, "%s\n", buf);
	
	bytesWritten = fprintf(stderr, "%s\n", buf);
}

__attribute__((constructor)) void mallocCounter() {
	fprintf(stderr, "start!\n");
	
	real_malloc = dlsym(RTLD_NEXT, "malloc");
	real_calloc = dlsym(RTLD_NEXT, "calloc");
	real_realloc = dlsym(RTLD_NEXT, "realloc");
	real_free = dlsym(RTLD_NEXT, "free");
	
	fprintf(stderr, "dlsym done!\n");
	
	//fd_out = creat("libmemchecker_log.txt", 0666);
	//fd_out = open("libmemchecker_log.txt", O_WRONLY | O_CREAT, 664);
	//fd_output = fopen("libmemchecker_log.txt", "w");
    
	//fprintf(stderr, "fd is %d!\n", fd_out);
    
	fprintf(stderr, "%s: %x\n", "malloc", real_malloc);
	fprintf(stderr, "%s: %x\n", "calloc", real_calloc);
	fprintf(stderr, "%s: %x\n", "realloc", real_realloc);
	fprintf(stderr, "%s: %x\n", "free", real_free);
    
	//sigset(SIGTSTP, flushLogWrapper);
    //atexit(flushLog);
}

void *calloc(size_t nmemb, size_t size){
	perror("calloc");
	if (!real_calloc){
		fprintf(stderr, "callot uninitialized yet.\n");
		mallocCounter();
	}
	void *lptr = real_calloc(nmemb, size);
	recordLog("+\t%lu\t%p\tcalloc\n", (long unsigned) size * nmemb, lptr);
	return lptr;
}

void *malloc(size_t size){
	perror("malloc");
	if (!real_malloc){
		fprintf(stderr, "mallot uninitialized yet.\n");
		mallocCounter();
	}
	void *lptr = real_malloc(size);
	recordLog("+\t%lu\t%p\tmalloc\n", (long unsigned) size, lptr);
	return lptr;
}

void *realloc(void *ptr, size_t size){
	perror("realloc");
	if (!real_realloc){
		fprintf(stderr, "realloc uninitialized yet.\n");
		mallocCounter();
	}
    void *lptr = real_realloc(ptr, size);
	recordLog("~\t%lu\t%p\t%p\trealloc\n", (long unsigned) size, ptr, lptr);
    return lptr;
}

void free(void *ptr){
	perror("free");
	if (!real_free) mallocCounter();
	recordLog("-\t%p\n", ptr);
    real_free(ptr);
}
