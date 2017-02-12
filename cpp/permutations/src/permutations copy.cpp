/*
 ============================================================================
 Name        : projTwo.c
 Author      : David Thompson
 Version     :
 Copyright   : Your copyright notice
 Description : permutations
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int k,n,perm = 1;
	printf("enter k\n");; /* enter k */

	scanf("%d",&k);
	printf("enter n\n");
	scanf("%d",&n);



	while(k > 0)
	{
		k--;
		perm = perm * (n - k);

	}

	printf("permutations = %d\n",perm);

	return EXIT_SUCCESS;
}
