#include <stdlib.h>
#include <stdio.h>
#include "private_customer.h"
#include <string.h>

void say_hello(customer_s* customer)
{
    printf("hello from customer %s %s\n", customer -> first_name, customer -> last_name);
}

customer_s * create_customer(char * first_name, char * last_name, int age){
    //creates a customer
    customer_s * customer = (customer_s *) malloc(sizeof(customer_s));
    if (customer == NULL)  
    {
        perror("error occurred requiring memory for customer \n");
        abort();
    }

    strncpy(customer-> first_name, first_name, sizeof(customer-> first_name));
    strncpy(customer-> last_name, last_name, sizeof(customer-> last_name));
    return customer;
}

void destroy_customer(customer_s * customer)
{
    free(customer);
}

