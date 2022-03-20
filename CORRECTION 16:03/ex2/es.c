/* es.c : gestion des entrees/sorties */
#include <unistd.h>

/* lireligne : lit une ligne depuis le perpherique deja ouvert dont le file
 descriptor est fd, dans le buffer b de taille t, jusqu'au delimiteur delim
 Retourne le nb de caracteres dans le buffer ou -1 si erreur */

int lireligne(int fd, void *b, int t, char delim)
{
void * d, *f;
   d = b;
   f = b+t;
   while (d < f) {
     if (read(fd,d,1) == -1) return -1;
     if (*(char*)d == delim) break;
     d++;
   }
   if (d==f) { /* depassement buffer */
      while (*(char*)b != delim) read(fd,b,1);
      return -1;
   }
   *(char*)d = '\0'; /* on transforme le delimiteur en caractere nul */
   return (d-b);
}

 

