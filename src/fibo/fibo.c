#include "fibo.h"

long long int fibo(int n){
	if (n == 1 || n == 2){
		return 1;
	} else {
		return fibo(n-1) + fibo(n-2);
	}
}

//fibonacci in a dynamic/iterative programming way

long long int fibo_iter(int n){
	long long int array[n];
    array[0] = array[1] = 1;
    for (int i = 2; i < n; i++){
        array[i] = array[i -1] + array[i-2];
    }
    return array[n-1];
}
