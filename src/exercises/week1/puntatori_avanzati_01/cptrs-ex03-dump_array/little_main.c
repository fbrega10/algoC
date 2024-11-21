#include <stdio.h>


int main()
{
    char * fp = "hello world\n";
    char * fp2 = "idc aslkdfjsdlkfjsdlkfjsdlkfjdsklfjdsklfjsdklfj\n";
    printf("%s", fp);
    printf("size 1 = %lu\n", sizeof(fp));
    printf("%s", fp2);
    printf("size 2 = %lu\n", sizeof(fp2));
    return 0;
}
