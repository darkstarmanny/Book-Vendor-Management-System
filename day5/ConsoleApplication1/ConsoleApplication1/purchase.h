#ifndef PURCHASE_H
#define PURCHASE_H
#include"item.h"

enum STATUS{ RAISED, DELIVERED };

typedef struct Order
{
	int po_id;
	item_t item;
	int vendor_id;
	float discount, total;
	char v_company[60];
	enum STATUS status;
}porder_t;

void input_purchase_order();
void write_porder_in_file(porder_t *po);
void read_porder_from_file();
void display_porder(porder_t *po);
int last_po_id(); 
int find_purchase_order_by_name(char *purchase, porder_t *po_out);
void received_order(); 
#endif