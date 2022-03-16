/* es.c gestion des entrées/sorties  */

/* lireligne : lit une ligne depuis le périférique déjà ouvert dont le file descriptor est fd, dans le buffer b de taille t, jusqu'au délimiteur delim , Retourne le nb de caractères dans le bufer ou -1 si erreur*/

#include <unistd.h>


lireligne(int fd, (void *)b, int t, char delim)
{
	void *d, *f;
	d = b;
	f = b + t;
	while (d < f){
		if (read(fd, d, 1) == -1)
			return -1;
		if (*(char*)d == delim) /* On transforme d de type void en char avec (char *), on cherche ensuite la valeur du pointeur avec * devant  */
			break;
		d++;
	}
	if (d == f)
	{ /* Dépassement de buffer  */
		while(*(char*)b != delim)
			read(fd, b, 1);
			return -1;
	}
	*(char*)d = '\0'; /* On transforme le delimiteur en caractère nul */
	return (d-b);
}









