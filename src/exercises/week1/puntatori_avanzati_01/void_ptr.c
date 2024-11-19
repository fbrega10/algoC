/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

#include <assert.h>
#include <stdio.h>

int main()
{
    int x = 1;
    int y = 0;
    void *vptr = NULL;
    int *iptr = NULL;
    double d = 0.5;
    double *dptr = NULL;
    char c = 'A';
    char *cptr = NULL;
    double ary[] = {-1, 0, 1};

    printf("\n*** Initialization\n");

    printf("&u: %p, x: %d\n", (void*) &x, x);
    printf("&v: %p, y: %d\n", (void*) &y, y);
    printf("&d: %p, d: %f\n", (void*) &d, d);
    printf("&c: %p, c: %c\n", (void*) &c, c);
    printf("&vptr: %p, vptr: %p\n", (void*) &vptr, (void*) vptr);
    printf("&iptr: %p, iptr: %p\n", (void*) &iptr, (void*) iptr);
    printf("&dptr: %p, dptr: %p\n", (void*) &dptr, (void*) dptr);
    printf("&cptr: %p, cptr: %p\n", (void*) &cptr, (void*) cptr);

    /* Assignment */

    printf("\n*** Assignment\n");

    /* Assign int* to void* and vice versa */
    printf("&x: %p, x: %d\n", (void*) &x, x);
    vptr = &x;
    printf("&vptr: %p, vptr: %p\n", (void*) &vptr, (void*) vptr);
    iptr = vptr;
    printf("&iptr: %p, iptr: %p, *iptr: %d\n", (void*) &iptr, (void*) iptr, *iptr);
    vptr = iptr;
    printf("&vptr: %p, vptr: %p\n", (void*) &vptr, (void*) vptr);
    /* Assign double* to void* and vice versa */
    printf("&d: %p, d: %f\n", (void*) &d, d);
    vptr = &d;
    printf("&vptr: %p, vptr: %p\n", (void*) &vptr, (void*) vptr);
    dptr = vptr;
    printf("&dptr: %p, dptr: %p, *dptr: %f\n", (void*) &dptr, (void*) dptr, *dptr);
    vptr = dptr;
    printf("&vptr: %p, vptr: %p\n", (void*) &vptr, (void*) vptr);
    /* Assign char* to void* and vice versa */
    printf("&c: %p, c: %c\n", (void*) &c, c);
    vptr = &c;
    printf("&vptr: %p, vptr: %p\n", (void*) &vptr, (void*) vptr);
    cptr = vptr;
    printf("&cptr: %p, cptr: %p, *cptr: %c\n", (void*) &cptr, (void*) cptr, *cptr);
    vptr = cptr;
    printf("&vptr: %p, vptr: %p\n", (void*) &vptr, (void*) vptr);

    /* Dereferencing */

    printf("\n*** Dereferencing\n");

    /* Get values */
    printf("\n**** Get values\n");
#if 0
    y = *vptr; /* NO! */
#endif
    printf("&x: %p, x: %d\n", (void*) &x, x);
    vptr = &x;
    iptr = vptr;
    y = *iptr;
    y = *((int*) vptr);
    printf("&y: %p, y: %d\n", (void*) &y, y);
    printf("&iptr: %p, iptr: %p, *iptr: %d\n", (void*) &iptr, (void*) iptr, *iptr);
    printf("&vptr: %p, vptr: %p, *vptr: %d\n", (void*) &vptr, (void*) vptr, *((int*) vptr));

    /* Set values */
    printf("\n**** Set values\n");
#if 0
    *vptr = y+1; /* NO! */
#endif
    printf("&y: %p, y: %d\n", (void*) &y, y);
    *((int*) vptr) = y+1;
    printf("&iptr: %p, iptr: %p, *iptr: %d\n", (void*) &iptr, (void*) iptr, *iptr);
    printf("&vptr: %p, vptr: %p, *vptr: %d\n", (void*) &vptr, (void*) vptr, *((int*) vptr));
    *iptr = y+1;
    printf("&iptr: %p, iptr: %p, *iptr: %d\n", (void*) &iptr, (void*) iptr, *iptr);
    printf("&vptr: %p, vptr: %p, *vptr: %d\n", (void*) &vptr, (void*) vptr, *((int*) vptr));

    /* Pointer arithmetic */

    printf("\n*** Pointer Arithmetic\n");

    vptr = ary;
    assert( *((double*) vptr) == ary[0] );
    printf("&ary: %p, ary: %p, *ary: %f\n", (void*) &ary, (void*) ary, *ary);
    printf("&vptr: %p, vptr: %p, *vptr: %f\n", (void*) &vptr, (void*) vptr, *((double*) vptr));

    /* Get values */
    printf("\n**** Get values\n");
#if 0
    ary[1] = vptr[1]; /* NO! */
#endif
    // Use of auxiliary variable
    printf("&ary[1]: %p, ary[1]: %f\n", (void*) &ary[1], ary[1]);
    dptr = vptr;
    assert( *dptr == ary[0] );
    vptr = dptr;
    printf("Use of auxiliary variable: %f\n", dptr[1]);
    printf("&dptr[1]: %p, dptr[1]: %f\n", (void*) &dptr[1], dptr[1]);
    printf("&vptr[1]: %p, vptr[1]: %f\n", (void*) &((double*) vptr)[1], ((double*) vptr)[1]);
    // Use of cast
    printf("&ary[1]: %p, ary[1]: %f\n", (void*) &ary[1], ary[1]);
    ary[1] = dptr[1];
    assert( ((double*) vptr)[1] == ary[1] );
    printf("Use of cast: %f\n", ((double*) vptr)[1]);
    ary[1] = ((double*) vptr)[1];
    assert( ((double*) vptr)[1] == ary[1] );
    printf("&dptr[1]: %p, dptr[1]: %f\n", (void*) &dptr[1], dptr[1]);
    printf("&vptr[1]: %p, vptr[1]: %f\n", (void*) &((double*) vptr)[1], ((double*) vptr)[1]);

    /* Set values */
    printf("\n**** Set values\n");
#if 0
    vptr[1] = ary[1]+1; /* NO! */
#endif
    // Use of auxiliary variable
    printf("&ary[1]: %p, ary[1]: %f\n", (void*) &ary[1], ary[1]);
    dptr = vptr;
    //((double*) vptr)[1] = ary[1]+1;
    //assert( ((double*) vptr)[1] == ary[1] );
    dptr[1] = ary[1]+1;
    assert( ((double*) vptr)[1] == ary[1] );
    printf("&dptr[1]: %p, dptr[1]: %f\n", (void*) &dptr[1], dptr[1]);
    printf("&vptr[1]: %p, vptr[1]: %f\n", (void*) &((double*) vptr)[1], ((double*) vptr)[1]);
    // Use of cast
    printf("&ary[1]: %p, ary[1]: %f\n", (void*) &ary[1], ary[1]);
    ((double*) vptr)[1] = ary[1]+1;
    assert( ((double*) vptr)[1] == ary[1] );
    printf("&dptr[1]: %p, dptr[1]: %f\n", (void*) &dptr[1], dptr[1]);
    printf("&vptr[1]: %p, vptr[1]: %f\n", (void*) &((double*) vptr)[1], ((double*) vptr)[1]);

    /* Arithmetic */
    printf("\n**** Arithmetic\n");
#if 0
    vptr = vptr+1; /* NO! */
#endif
    vptr = &ary[1];
    assert( *((double*) vptr) == ary[1] );
    vptr = dptr+1;
    assert( *((double*) vptr) == ary[1] );
    printf("&ary[1]: %p, ary[1]: %f\n", (void*) &ary[1], ary[1]);
    printf("&dptr[1]: %p, dptr[1]: %f\n", (void*) &dptr[1], dptr[1]);
    printf("vptr: %p, *vptr: %f\n", (void*) vptr, *((double*) vptr));

    /* Assignment != Cast */

    printf("\n*** Assignment is not Cast\n");

    x = 64;
    c = 'A';
    printf("&x: %p, x: %d\n", (void*) &x, x);
    printf("&c: %p, c: %c\n", (void*) &c, c);
    vptr = &x;
    cptr = vptr;
    printf("&vptr: %p, vptr: %p, *vptr: %d\n", (void*) &vptr, (void*) vptr, *((int*) vptr));
    printf("&cptr: %p, cptr: %p, *cptr: %c\n", (void*) &cptr, (void*) cptr, *cptr);
    assert( *cptr == '@' );
    assert( *cptr == (char) x );
    vptr = &c;
    iptr = vptr;
    printf("&vptr: %p, vptr: %p, *vptr: %c\n", (void*) &vptr, (void*) vptr, *((char*) vptr));
    printf("&iptr: %p, iptr: %p, *iptr: %d\n", (void*) &iptr, (void*) iptr, *iptr);
    if (sizeof(int) != sizeof(char))
    {
        assert( *iptr != (int) 'A' );
        assert( *cptr != (int) c );
    }
    else
    {
        assert( *iptr == (int) 'A' );
        assert( *cptr == (int) c );
    }

    /* Pointer cast != Value cast */

    printf("\n*** Pointer Cast is not Value Cast\n");

    d = 10.25;
    vptr = &d;
    printf("---- *((int*) vptr) != (int) *((double*) vptr)\n");
    printf("[right pointer cast] &vptr: %p, vptr: %p, *vptr: %g\n", (void*) &vptr, (void*) vptr, *((double*) vptr));
    printf("[wrong pointer cast] &vptr: %p, vptr: %p, *vptr: %d\n", (void*) &vptr, (void*) vptr, *((int*) vptr));
    printf("[value cast after right pointer cast] &vptr: %p, vptr: %p, *vptr: %d\n", (void*) &vptr, (void*) vptr, (int) *((double*) vptr));

    c = '@';
    vptr = &c;
    printf("---- *((int*) vptr) != (int) *((char*) vptr)\n");
    printf("[right pointer cast] &vptr: %p, vptr: %p, *vptr: %c\n", (void*) &vptr, (void*) vptr, *((char*) vptr));
    printf("[wrong pointer cast] &vptr: %p, vptr: %p, *vptr: %d\n", (void*) &vptr, (void*) vptr, *((int*) vptr));
    printf("[value cast after right pointer cast] &vptr: %p, vptr: %p, *vptr: %d\n", (void*) &vptr, (void*) vptr, (int) *((char*) vptr));

    /* However, in case of compatible types, the results is as expected; e.g., since `char` is an integral type and `sizeof(char)` <= `sizeof(int)`, the two casts are equivalent in the following situation:
    x = 64;
    vptr = &x;
    printf("---- *((char*) vptr) == (char) *((int*) vptr)\n");
    printf("[pointer cast to right type] &vptr: %p, vptr: %p, *vptr: %d\n", (void*) &vptr, (void*) vptr, *((int*) vptr));
    printf("[pointer cast to other type] &vptr: %p, vptr: %p, *vptr: %c\n", (void*) &vptr, (void*) vptr, *((char*) vptr));
    printf("[value cast after pointer cast to right type] &vptr: %p, vptr: %p, *vptr: %c\n", (void*) &vptr, (void*) vptr, (char) *((int*) vptr));
    */

    return 0;
}
