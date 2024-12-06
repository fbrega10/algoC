typedef struct customer_s {
    int age;
    char first_name[20];
    char last_name[20];
} customer_s;

typedef struct order_s  {
    char object_name[30];
    int quantity;
} order_s;

void say_hello(customer_s* customer);

customer_s * create_customer(char *, char *, int );
void destroy_customer(customer_s *);
