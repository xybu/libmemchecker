all:
	gcc -g -c memchecker.c
	ar rcu libmemchecker.a memchecker.o
	gcc -g -std=gnu99 -o test test.c -L. -lmemchecker

clean:
	rm *.a *.o test
