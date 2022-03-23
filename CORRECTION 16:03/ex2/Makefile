# Makefile pour les exemples

default : ex1 ex1s ex2 testll testll2

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

testll : testll.o es.o
	cc -o testll testll.o es.o

testll2 : testll.o libtot.a
	cc -o testll2 testll.o libtot.a

testll.o : testll.c es.h
	cc -c testll.c

es.o : es.c es.h
	cc -c es.c

libtot.a : malib.o es.o
	ar crv libtot.a malib.o es.o


clean :
	rm -f ex1 ex1s ex2 testll testll2 libtot.a *.o

