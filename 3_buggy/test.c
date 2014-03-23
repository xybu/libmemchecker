#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
	//malloc
	int *a = malloc(sizeof(int));
	*a = 5;
	printf("%d\n", *a);
	
	int *b = calloc(2, sizeof(int));
	b[0] = 'a';
	b[1] = 'b';
	printf("%c %c\n", b[0], b[1]);
	
	b = realloc(b, 3 * sizeof(int));
	b[2] = 'c';
	printf("%c %c %c\n", b[0], b[1], b[2]);	
	
	char *c = strdup("test123");
	printf("%s\n", c);
	
	free(a);
	free(b);
	free(c);
	
	return 0;
}
