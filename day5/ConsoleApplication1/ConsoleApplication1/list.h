#ifndef LIST_H
#define LIST_H
#include"item.h"

void input_itm(item_list_t *s);
void display_itm(item_t *s);
void init_head(item_list_t *list);
item_node_t * create_node(item_t *stud);
void add_last(item_t item, item_list_t *list);
void display_list(item_list_t *list);
void write_link_list_in_stock(item_list_t *head);
void load_items_from_stock_to_link_list(item_list_t *head);
#endif