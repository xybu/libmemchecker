all:
	gcc -c memchecker.c
	ar rcu libmemchecker.a memchecker.o
	gcc -Wl,-wrap,malloc -Wl,-wrap,free -o test test.c -L. -lmemchecker
	rm *.a *.o