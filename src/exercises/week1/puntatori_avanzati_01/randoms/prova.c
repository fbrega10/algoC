#include <stdio.h>
#include <stdlib.h>
#define N 30


int main()
{
    int * ptr = NULL;
    ptr = (int*) calloc(1, sizeof(int));
    printf("current value : %d \n", *ptr);
    for (size_t i = 0; i < N; ++i)
    {
        *ptr = (int)i;
        printf("current value : %d \n", *ptr);
    }
    free(ptr);
}
