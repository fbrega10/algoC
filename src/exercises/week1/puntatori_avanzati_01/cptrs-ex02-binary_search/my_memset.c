#include <stdio.h>
#include <stdlib.h>


void my_memset(void * buf, void * value, size_t size);

int main()
{
    int c = 6;
    int * buf = (int *) malloc(sizeof(int));
    my_memset((void *)buf, &c, sizeof(int));
    printf("value = %d , value2 = %d\n", *buf, c);
    free(buf);
    return EXIT_SUCCESS;
}


void my_memset(void * buf, void * value, size_t size){
    unsigned char * ptr = buf;
    unsigned char * val = value;
    for (size_t i = 0; i < size; ++i)
        ptr[i] = val[i];
}
