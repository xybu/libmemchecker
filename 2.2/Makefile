all:
	gcc memchecker.c -shared -fPIC -ldl -o libmemchecker.so || touch libmemchecker.so
	LD_LIBRARY_PATH=.
	LD_PRELOAD=./libmemchecker.so
	gcc -std=gnu99 -c test.c
	gcc -fPIC -Wall -o test test.o

clean:
	rm *.a *.so test
