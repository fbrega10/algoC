#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct user_t{
    char name [100];
};
typedef struct user_t user_t;

int main(int argc, char *argv[]) {
    int * buffer = malloc(sizeof(int));
    user_t * user = (user_t *) malloc(sizeof(user_t));
    user_t * user2 = malloc(sizeof(user_t));
    strcpy(user-> name, "John Doe");
    printf("name %s\n", user -> name);
    printf("size of %lu %lu %lu\n", sizeof(user), sizeof(user2), sizeof(buffer));
    free(user);
    free(user2);
    free(buffer);
  return EXIT_SUCCESS;
}

/*
 * Es 1 -> stampa 10 e a capo
 * Es 2  :
 * 11
 * 1
 * 2
 * 1
 *
 * Es 3 :
 *
 * 0
 * 2 0
 * 3 0
 *
 * Es 4
 * d = 3.2 x = 0 -> double
 * i = 2 y = 0 -> int
 *
 *
 * 3.2
 * precision sbagliata facendo double / int
 *
 *
 * Es 5:
 *
 * x = 10, y = 10
 * sommatoria da 1 a  10 -> y = 10, x = somm
 * y = z = 11, x = 9
 *
 * Es 7:
 *
 *
 * Es 11:
 *
 * sono uguali
 *
 * Es 12:
 * OK
 *
 * Es 13:
 * x = 10
 *
 *
 * Es 14:
 * green 
 * blue 
 * Unknown
 *
 * Es 15:
 * stampa i da n a 0
 *
 *
 * Es 16:
 * stampa i da n a 1
 *
 * es 17:
 *
 * v = 2
 *
 * Es 18 :
 *
 * Segmentation fault
 *
 *
 * Es 19:
 *
 * sono due size differenti 
 * una è del puntatore a int 
 * l'altra è del tipo intero
 *
 *
* Es 20:
* hanno due size differenti
*
*
* Es 21 :
*
* 1 e 1
*
* Es 22 :
* stiamo allocando sullo stack una variabile
* e ritornando l'indirizzo di memoria di una variabile che vive sullo stack 
* e non l'heap (memoria dinamica).
* Causa segmentazione di memoria perchè di ritorno dalla funzione (pop)
* le variabili locali vengono liberate
* 
* Es 23:
*
* non copia il valore dei due puntatori, non li dereferenzia
*
* Es 24 :
*
* Non è stato castato il puntatore al tipo *user_t
*
*/
