#Makefile pour les exemples

#exemple1: exemple1.c
#	cc -o exemple1 exemple1.c
#clean:
#	rm -f exemple1


exemple1: exemple1.c malib.h
	cc -c exemple1.c

malib.o: malib.c malib.h
	cc -c malib.c

clean:
	rm -f exemple1 *.o
