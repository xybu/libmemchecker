#include "test.h"
#include <stdio.h>
#include <stdlib.h>

int main(void){
	//malloc
	int *a = malloc(sizeof(int));
	
	*a = 5;
	printf("%d\n", *a);
	
	free(a);
	
	return 0;
}
