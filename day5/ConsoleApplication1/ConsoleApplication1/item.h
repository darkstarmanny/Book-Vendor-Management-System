#ifndef ITEM_H
#define ITEM_H

typedef struct Item
{
	int itemid;
	char product_Name[100];
	char product_Description[100];
	int  quantity;
	float unit_price;
	float total;
}item_t;

typedef struct item_node
{
	item_t item;
	int count;
	struct item_node *next;
}item_node_t;

typedef struct item_list
{
	item_node_t *head;
}item_list_t;

void input_items(item_t *item);
void write_item_in_file(item_t *item);
void read_item_from_file();
int find_item_by_name(char *pname, item_t *itout);
void display_item(item_t *item);
int last_item_id();
#endif