/* ex1.c : exemple simple de prograame en C */
#include <stdio.h>

#define VAL1 234

int toto(int a, int b) /* calcule la somme de 2 entiers */
{
   return a+b;
}

int main(int N, char *P[])
{
int i, j, k;
   i=VAL1;
#ifdef TRACE
     printf("i vaut %d\n", i);
#endif
   j=78;
   k=toto(i,j);
   printf("k = %d\n",k);
   return 0;
}

