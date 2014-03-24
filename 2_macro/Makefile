all:
	gcc -g -c memchecker.c
	ar rcu libmemchecker.a memchecker.o
	@echo '#include "memchecker.h"' | cat - test.c > t_tmp && mv t_tmp test.c
	@echo 'gcc -g -std=gnu99 -o test test.c -L. -lmemchecker'
	@gcc -g -std=gnu99 -o test test.c -L. -lmemchecker

clean:
	rm *.a *.o test *.txt
