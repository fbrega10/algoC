#include <stdio.h>
#include <stdlib.h>
#include "fibo.h"

int main(){
	printf("insert the number of steps you want to advance on the fibonacci algorithm: \n");
	int n;
	scanf("%d", &n);
	printf("the result is : %lld\n", fibo(n));
	return EXIT_SUCCESS;
}
