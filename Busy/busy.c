
/* exmeple simple pour illustrer le principe de la busybox */
#include <stdio.h>
#include <string.h>

#define LCOM 24
/* structure pour chaque element du tableau des commandes */
struct Elt
{
	char comm[LCOM]; /* nom de la commande */
	int (*f) (int, char **);
};

#ifdef F_DF_
/* On suppose que la busybox supporte les commandes df du cat */
int df(int N, char *P[])
{
	printf("Execution du code de df avec %d paramètres ! \n", N-1);
	return 0;
}

#endif
#ifdef F_DU_
int du(int N, char *P[])
{
	printf("Execution du code de du avec %d paramètres ! \n", N-1);
	return 0;
}

#endif
#ifdef F_CAT_
int cat(int N, char *P[])
{
	printf("Execution du code de cat avec %d paramètres ! \n", N-1);
	return 0;
}

#endif

/* le tableau contenant la liste des elements */
struct Elt Tab[] = {
	#ifdef F_DF_
		"df", df,
	#endif
	#ifdef F_DU_
		"du", du,
	#endif
	#ifdef F_CAT_
		"cat", cat,
	#endif
	"", NULL
};

int main(int N, char *P[])
{
	int i = 0;
	char *comm;
	/* On isole le nom de la commande dans le cas d'un chemin */
	if ((comm = strrchr(P[0], (int)'/')) == NULL) comm == P[0];
	else comm++;
	/* Recherche dans la liste des commandes supportées */
	while (strlen(Tab[i].comm) > 0){
		if(strcmp(Tab[i].comm, comm) == 0)
			return Tab[i].f(N, P);
			i++;
	}
	printf("Fonction busy non suppotée ! \n");
	return 1;
}
