#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

void cpy(void * ptr, void * ptr2, size_t size);

int main()
{
    int * i = (int *) malloc(sizeof(int));
    *i = 3;

    int * c = (int *) malloc(sizeof(int));
    *c = 35;

    printf("i = %d, c = %d\n", *i, *c);
    void (*func)(void *, void *, size_t) = cpy;
    size_t s = sizeof(int);
    func((void *)&i,(void *)&c, s);

    printf("AFTER : \ni = %d, c = %d\n",*i,*c);
    free(c);
    free(i);
}

void cpy(void * ptr, void * ptr2, size_t size)
{
    unsigned char * cpy1 = ptr;
    unsigned char * cpy2 = ptr2;
    unsigned char temp = *cpy1;
    for (size_t i = 0; i < size; i++)
    {
        temp = cpy1[i];
        cpy1[i] = cpy2[i];
        cpy2[i] = temp;
    }
}
