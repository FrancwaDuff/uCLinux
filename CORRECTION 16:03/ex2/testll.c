/* test de la fonction lire ligne  */
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include "es.h"

#define LBUF 200
char buf[LBUF];
int RUN=1;

/* Fonction qui va être appelé au moment de la reception du signal. */

void Enable_raw_mode()
{
	struct termios raw;
	tcgetattr(STDIN_FILENO, &raw);
	raw.c_lflag &= ~(ECHO);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

}


void interrupt(int S)
{
	switch(S){
	case SIGINT :
		RUN=0;
		break;
	default :
		fprintf(stderr, "Recu signal %d ????\n", S);
	}

}
/* Trouver comment mettre le terminal en mode RAW */

int main(int N, char *P[])
{
	Enable_raw_mode();

	int n;
	signal(SIGINT, interrupt);
	while (RUN){
		printf("Taper un texte ou FIN pour stopper le programme :\n");
		if ((n = lireligne(0, (void *)buf, LBUF, '\n')) < 0)
			printf("Erreur dans la saisie de la ligne!");
		else
			if(strcmp(buf, "FIN") == 0) break;
			printf("%d caractères: <%s>\n", n, buf);
	}
	printf("Fin du programme.\n");
	return 0;

}


