# Makefile pour les exemples

default : ex1 ex1s ex2

ex1 : ex1.c
	cc -o ex1 ex1.c

ex1s : ex1.c
	cc -o ex1s -static ex1.c

ex2 : ex2.o malib.o
	cc -o ex2 ex2.o malib.o

ex2.o : ex2.c malib.h
	cc -c ex2.c

malib.o : malib.c malib.h
	cc -c malib.c

clean :
	rm -f ex1 ex1s ex2 *.o

