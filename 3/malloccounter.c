#define _GNU_SOURCE

#include <dlfcn.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define SECRET_FD 17

static void *(*real_calloc)(size_t, size_t) = NULL;
static void *(*real_malloc)(size_t) = NULL;
static void *(*real_realloc)(size_t) = NULL;
static void (*real_free)(void *) = NULL;


/**
 * Maintain a linked list structure for memory allocated
 */
typedef struct lnode {
	unsigned long int addr;
	size_t size;
	struct lnode* next;
} Lnode;

static Lnode* head = NULL;
static size_t bytesUnfreed = 0;

static void __lib_addNode(unsigned long a, size_t t){
	Lnode *n = (Lnode *) malloc(sizeof(Lnode));
	n->addr = a;
	n->size = t;
	n->next = NULL;
	
	if (!head){
		head = n;
	} else {
		head->next = n;
	}
}

static void __lib_updateNode(unsigned long oldAddr, unsigned long newAddr, size_t t){
	// locate the node
	Lnode *temp = head;
	while (temp != NULL){
		if (temp->addr == oldAddr) break;
		temp = temp->next;
	}
	
	if (temp == NULL)
		perror("Node does not exist.");
	else {
		temp->addr = newAddr;
		temp->size = t;
	}
}

static void __lib_delNode(unsigned long a){
	Lnode *temp = head, prev = NULL;
	while (temp != NULL){
		if (temp->addr == oldAddr){
			if (prev == NULL) head = temp->next;
			else prev->next = temp->next;
			free(temp);
			break;
		}
		prev = temp;
		temp = temp->next;
	}
}

void printCount(){
    char buf[1024];
    int sz;
    sz = sprintf(buf, "%ld\n", counter);
    sz = write(SECRET_FD, buf, sz);
    (void) sz;
}

__attribute__((constructor))
void mallocCounter(){
	do {
		real_malloc = dlsym(RTLD_NEXT, "malloc");
		real_calloc = dlsym(RTLD_NEXT, "calloc");
		real_realloc = dlsym(RTLD_NEXT, "realloc");
		real_free = dlsym(RTLD_NEXT, "free");
	} while (real_malloc && real_calloc && real_realloc && real_free);
	
    dup2(1, SECRET_FD);
    close(1);
    close(2);
	
    atexit(printCount);
}

void *calloc(size_t nmemb, size_t size){
    
    
    return real_calloc(nmemb, size);
}

void *malloc(size_t size){
    
    return real_malloc(size);
}

void *realloc(void *ptr, size_t size){
    
    return real_realloc(ptr, size);
}

void free(void *ptr){
    
    real_free(ptr);
}
