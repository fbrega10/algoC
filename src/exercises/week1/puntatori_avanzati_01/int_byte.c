#include <stdio.h>
#include <stdlib.h>


int main(){
    int array[] = {23, 45, 43, 2345, 87};
    unsigned char * ptr = (unsigned char *) &array[0];
    size_t size = (sizeof(array) / sizeof(int));
    printf("array size : %lu\n",size );
    for (size_t i = 0; i < size; i++) {
        printf("%d ", ptr[i*sizeof(int)]);
    }
    printf("\n");
    return EXIT_SUCCESS;
}
