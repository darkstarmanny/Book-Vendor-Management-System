#include<stdio.h>
#include<conio.h>
#include<string.h>
#include"list.h"
#include"purchase.h"
#include"item.h"

void input_itm(item_list_t *l)
{
	char product[32];
	int flag;
	porder_t po,pt;
	item_t it;
	FILE *fp;
	int size = sizeof(pt);
	read_porder_from_file(&po);
	printf("\nEnter Product Name :");
	scanf("%s",product);
	flag = find_purchase_order_by_name(product, &po);
	if (flag == 1)
	{
		it.itemid = last_item_id() + 1;
		strcpy(it.product_Name,po.item.product_Name);
		it.quantity = po.item.quantity;
		it.unit_price = po.item.unit_price;

		fp = fopen("PURCHASE.DAT", "rb+");
		if (fp == NULL)
		{
			printf("\nUnable to Open File in Input Item\n");
			return;
		}
		while (fread(&pt, sizeof(pt), 1, fp) != 0)
		{
			if (strcmp(it.product_Name, pt.item.product_Name) == 0)
			{

				pt.status = DELIVERED;
				fseek(fp, -size, SEEK_CUR);
				fwrite(&pt, sizeof(pt), 1, fp);
				printf("staus is updated \n");
				fclose(fp);
			}

		}
	}
	add_last(it, l);
}



void display_itm(item_t *it)
{
	printf(" %d\t\t%s\t\t\t%d\t\t%f\n", it->itemid, it->product_Name,it->quantity,it->unit_price);
}

void init_head(item_list_t *list)
{
	list->head = NULL;
	//list->count = 0;
}

item_node_t * create_node(item_t *item)
{
	item_node_t * newnode = (item_node_t*)malloc(sizeof(item_node_t));
	newnode->item = *item;
	newnode->next = NULL;
	return newnode;
}


void add_last(item_t item, item_list_t *list)
{
	item_node_t * newnode = create_node(&item);

	if (list->head == NULL)
	{
		list->head = newnode;
	}
	else
	{
		item_node_t *trav = list->head;
		while (trav->next != NULL)
		{
			trav = trav->next;
		}
		trav->next = newnode;
	}
}

void display_list(item_list_t *list)
{
	item_node_t *trav = list->head;
	printf("\n-----------------------------------------------------------------------------\n");
	printf("\nItem id: \tProduct Name:\tQuantity: \tUnit Price: \n");
	printf("\n-----------------------------------------------------------------------------\n");
	while (trav != NULL)
	{
		display_itm(&trav->item);
		trav = trav->next;
	}
	printf("\n-----------------------------------------------------------------------------\n");
}
void write_link_list_in_stock(item_list_t *list)
{
	FILE *fp;
	item_node_t *trav = list->head;
	
	fp = fopen("STOCK.DAT", "ab");
	if (fp == NULL)
	{
		printf("Unable to open file \n");
	}
	else
	{
		while (trav!=NULL)
		{
			fwrite(&trav->item, sizeof(item_t), 1, fp);
			trav = trav->next;
		}
	}
	fclose(fp);
	
}

void load_items_from_stock_to_link_list(item_list_t *list)
{
	FILE *fp;
	item_t it;
	item_list_t *trav = list->head;

	fp = fopen("STOCK.DAT", "rb");

	if (fp == NULL)
	{
		printf("unable to open file \n");
		return;
	}
	else
	{
		while (fread(&it, sizeof(it), 1, fp) != NULL)
		{
			add_last(it, list);
		}
	}
		fclose(fp);
		display_list(list);
}

//int main()
//{
//	int choice;
//	item_t s;
//	item_list_t list;
//	init_head(&list);
//	
//	load_items_from_stock_to_link_list(&list);
//	do
//	{
//		printf("1.Input Student\n2.Show Students\nEnter Choice : ");
//		scanf("%d", &choice);
//
//		switch (choice)
//		{
//		case 1:
//			input_itm(&list);
//			//add_last(s, &list);
//			break;
//		case 2:
//			display_list(&list);
//			break;
//		case 3:
//			break;
//		}
//	} while (choice != 0);
//	write_link_list_in_stock(&list);
//	return 0;
//}