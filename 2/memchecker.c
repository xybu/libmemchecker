#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static FILE* fd_output = NULL;
static char *fd_fName = "libmemchecker_result.txt";

void finishOff(){
	fflush(fd_output);
	fclose(fd_output);
}

__attribute__((constructor))
void memchecker(){
	fd_output = fopen(fd_fName, "w");
	atexit(finishOff);
}

void * __mlib_malloc (size_t size) {
	void *lptr = malloc(size);
	if (lptr)
		fprintf(fd_output, "+\t%lu\t%p\tmalloc\n", (long unsigned) size, lptr);
	return lptr;
}

void *__mlib_calloc(size_t nmemb, size_t size){
	void *lptr = calloc(nmemb, size);
	if (lptr)
		fprintf(fd_output, "+\t%lu\t%p\tcalloc\n", (long unsigned) size * nmemb, lptr);
	return lptr;
}

void *__mlib_realloc(void *ptr, size_t size){
	void *lptr = realloc(ptr, size);
	if (lptr)
		fprintf(fd_output, "~\t%lu\t%p\t%p\trealloc\n", (long unsigned) size, ptr, lptr);
	return lptr;
}

char *__mlib_strdup(const char *str){
	int len = strlen(str);
	char *sptr = malloc(len);
	if (sptr){
		strcpy(sptr, str);
		fprintf(fd_output, "+\t%lu\t%p\tstrdup\n", (long unsigned) len, sptr);
	}
	return sptr;
}

void __mlib_free(void * ptr) {
	fprintf(fd_output, "-\t%p\n", ptr);
	free(ptr);
}
