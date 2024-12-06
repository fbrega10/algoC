#include "public_customer.h"
#include <stdlib.h>

int main(){
    customer_t customer = create_customer("fabio", "brega", 24);
    say_hello(customer);
    destroy_customer(customer);
    return EXIT_SUCCESS;
}
