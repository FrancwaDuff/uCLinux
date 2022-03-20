/* ex2.c : exemple simple de prograame en C qui utilise malib.c */
#include <stdio.h>
#include "malib.h"

#define VAL1 234

int main(int N, char *P[])
{
int i, j, k;
   i=VAL1;
#ifdef TRACE
     printf("i vaut %d\n", i);
#endif
   j=78;
   k=toto(i,j);
   printf("k = %d avec toto\n",k);
   k=titi(i,j);
   printf("k = %d avec titi\n",k);
   return 0;
}

