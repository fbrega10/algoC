/* Esercizio:
   lavora con puntatori a funzioni per implementare una funzione num_apply
   per manipolare ogni elemento di un array di double
*/

#include <math.h>
#include <stddef.h>
#include <stdio.h>

void num_apply(double (*func)(double), double *par, size_t n) {
  size_t i;
  for (i = 0; i < n; i++) {
    par[i] = func(par[i]);
  }
}

double sqr(double x) { return x * x; }
double mult2(double x) { return 2 * x; }

int main() {
  double dary[] = {4, 16, 36};
  size_t n = sizeof dary / sizeof dary[0];

  // Applica ora le funzioni sqr, mult2, e sqrt (da math.h)
  num_apply(sqrt, dary, n); // -> {2, 4, 6}
  // Print array dary on the standard output
  printf("Modified Array after sqrt: {%lf, %lf, %lf}\n", dary[0], dary[1],
         dary[2]);

  num_apply(mult2, dary, n);
  printf("Modified Array after mult2: {%lf, %lf, %lf}\n", dary[0], dary[1],
         dary[2]);

  num_apply(sqr, dary, n);
  printf("Modified Array after sqr: {%lf, %lf, %lf}\n", dary[0], dary[1],
         dary[2]);

  return 0;
}
