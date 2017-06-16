#ifndef BILL_H
#define BILL_H
#include"list.h"
typedef struct bill
{
	int bill_id;
	char customer_name[32];
	int day, month, year;
	char product_name[32];
	int quantity;
	float unit_price;
	float total;
}bill_t;

void add_items_in_cart_list(item_list_t *list, item_list_t *cart);
void display_cart_list(item_list_t *cart);
void write_bill_in_file(bill_t *po);
void read_bill_from_file();
void generate_bill(bill_t *b,item_list_t *cart);
void getTodaysDate(bill_t *b);

#endif