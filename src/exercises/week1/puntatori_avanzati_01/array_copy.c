#include <stdio.h>
#include <stdlib.h>

void array_copy(void*ptr1, void *ptr2, size_t size);


int main(){
    int src[] = {23, 23, 45, 44};
    int dst[] = {21, 26, 43, 41};
    printf("before ");
    for (size_t i = 0; i < sizeof(src)/sizeof(int); i++)
        printf("%d ", dst[i]);
    printf("\n");

    array_copy(dst, src, sizeof(src));
    printf("after ");
    for (size_t i = 0; i < sizeof(src)/sizeof(int); i++)
        printf("%d ", dst[i]);
    printf("\n");
}


void array_copy(void*ptr1, void *ptr2, size_t size){
    unsigned char * dst = ptr1;
    unsigned char * src = ptr2;
    for (size_t i = 0; i < size; i++){
        dst[i] = src[i];
    }
}
