/* test de la fonction lire ligne  */
#include <stdio.h>
#include "es.h"

#define LBUF 200
char buf[LBUF];

int main(int N, char *P[])
{
	int n;
	while (1){
		printf("Taper un texte :\n");
		if ((n = lireligne(0, (void *)buf, LBUF, '\n')) < 0)
			printf("Erreur dans la saisie de la ligne!");
		else printf("%d caractères: <%s>\n", n, buf);
	}
	printf("Fin du programme");
	return 0;

}


