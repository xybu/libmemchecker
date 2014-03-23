all:
	gcc -O2 -g -shared -fPIC -o libmalloccounter.so malloccounter.c -ldl
	gcc -O2 -g -o test test.c

clean:
	rm -f libmalloccounter.so
	rm -f *.o testlist a.out
