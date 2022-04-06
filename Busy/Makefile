# Makefile de la busybox

OPTION = -DF_DF_ -DF_DU_ -DF_CAT

busy : busy.c
	cc -o busy $(OPTION) busy.c
	ln busy df
	ln busy du
	ln busy cat
clean :
	rm -f busy df du cat
