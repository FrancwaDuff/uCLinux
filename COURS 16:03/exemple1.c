/* ex1 */

#include "malib.h"
#include <stdio.h>

#define VAL1 234


int main(int N, char *P[])
{
	int i, j, k;
	i = VAL1;

	#ifdef TRACE
		printf("i vaut %d\n", i);
	#endif

	j = 78;
	k = toto(i,j);
	printf("k = %d\n", k);
	return 0;
}
