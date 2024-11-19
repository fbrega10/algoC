#include <stdio.h>
#include <stdlib.h>

double factorial(double s);
double pow(double s, double c);

int main(){

    double s = 5;
    double c = 3;
    double (*ptr)(double, double) = pow;
    double (*ls)(double) = factorial;
    printf("%f\n", ptr(s, c));
    printf("%f\n", ls(s));
    printf("this is the address of ptr %p and ls %p\n", ptr, ls);

    return EXIT_SUCCESS;
}


double factorial(double s){
    if (s == 1) return 1;
    else return s * factorial(s - 1.0);
} 

double pow(double s, double c){
    double result = s;
    for (size_t i = 0; i < c - 1;  i++)
    {
        result *= s;
    }
    return result;
}
