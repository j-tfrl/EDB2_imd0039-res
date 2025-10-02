all: asbin 

asbin: asbin.o arvSBfunc.o
	gcc -g -Wall -o asbin asbin.o arvSBfunc.o

asbin.o: asbin.c arvSBin.h
	gcc -c asbin.c

arvSBfunc.o: arvSBfunc.c arvSBin.h
	gcc -c arvSBfunc.c

test: all
	./asbin

clean: 
	rm -f asbin *.o