#ifndef CUSTOMER_H
#define CUSTOMER_H

typedef struct Customer
{
	char name[30];
	char lastname[30];
	char email[30];
	char contactno[30];
}customer_t;
void input_customer(customer_t *cust); 
void write_customer_in_file(customer_t *cust);
void read_customer_from_file();
int find_customer(char *name, customer_t *cu);
void display_customer(customer_t *cust);
#endif