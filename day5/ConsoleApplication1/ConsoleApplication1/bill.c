#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<time.h>
#include"bill.h"
#include"customer.h"
#include "item.h"


void add_items_in_cart_list(item_list_t *list, item_list_t *cart)
{
	char pname[30];
	printf("Enter product Name:");
	int quantity, demanded, original;
	float item_total;
	scanf("%s", pname);
	printf("Enter quantity required:");
	scanf("%d", &quantity);
	item_node_t *trav = list->head;
	while (trav != NULL)
	{
		if (strcmp(trav->item.product_Name, pname) == 0)
		{


			original = trav->item.quantity;
			demanded = quantity;
			item_total = trav->item.unit_price*quantity;
			trav->item.total= item_total;
			trav->item.quantity = demanded;
			add_last(trav->item, cart);
			trav->item.quantity = original - demanded;
			break;
		}
		trav = trav->next;
	}
}

void id_setter(item_list_t *cart)
{
	int id = 1;
	item_node_t *trav = cart->head;
	if (trav == NULL)
		return;
	while (trav != NULL)
	{

		trav->item.itemid = id;
		id++;
		trav = trav->next;
	}
}


void display_cart_list(item_list_t *cart)
{
	
	id_setter(cart);
	printf("\n-----------------------------------------------------------------------------\n");
	printf("\nItem id: \tProduct Name:\t\tQuantity: \tUnit Price: \n");
	printf("\n-----------------------------------------------------------------------------\n");
	item_node_t *trav = cart->head;
	while (trav != NULL)
	{
		display_itm(&trav->item);
		trav = trav->next;
	}
	printf("\n-----------------------------------------------------------------------------\n");
}

void write_bill_in_file(bill_t *po)
{
	FILE *fp;
	fp = fopen("BILL.DAT", "ab");
	if (fp == NULL)
	{
		printf("Unable to open file \n");
	}
	else
	{
		fwrite(po, sizeof(*po), 1, fp);
	}
	fclose(fp);
}
void read_bill_from_file()
{
	FILE *fp;
	bill_t b;

	fp = fopen("BILL.DAT", "rb");

	if (fp == NULL)
	{
		printf("unable to open file \n");
	}
	else
	{
		
		while (fread(&b, sizeof(b), 1, fp) != NULL)
		{
			printf("\n--------------------------------------------------------------------------\n");
			printf("\nDate\t\tCustomer Name\tTotal\n");
			printf("\n--------------------------------------------------------------------------\n");
			printf("%d/%d/%d\t%s\t\t%f\t\n", b.day, b.month, b.year, b.customer_name, b.total);
			printf("\n--------------------------------------------------------------------------\n");
		}
	}
}

void generate_bill(bill_t *b, item_list_t *cart)
{
	FILE *fp;
	int ret;
	char no[20];
	customer_t c;
	item_node_t *trav = cart->head;
	b->total = 0;
	printf("\n\nEnter the No of Customer::\n\n");
	scanf("%s", no);

	b->bill_id = last_bill_id() + 1;
	printf("\t\t\t\tBILL NO::%d", b->bill_id);
	getTodaysDate(b);
	printf("\t\t\tDate::%d/%d/%d", b->day, b->month, b->year);
	printf("\n\n\t\t\t\t==Amazon Book Store==");

	ret = find_customer(no, &c);
	if (ret == 1)
	{
		strcpy(b->customer_name, c.name);
		printf("\n\nName::%s %s", c.name, c.lastname);

	}
	else
		printf("\n\nCustomer not Present");

	display_cart_list(cart);
	while (trav != NULL)
	{
		b->total += trav->item.total;
		trav = trav->next;
	}
	printf("\n\t\t\tTotal::%.2f", b->total);
	fp = fopen("BILL.DAT", "ab");
	if (fp == NULL)
	{
		printf("\nUnable to Open Bill File in Write");
	}
	else
	{
		fwrite(b, sizeof(bill_t), 1, fp);
		
	}
	fclose(fp);
}

float total(item_list_t *cart)
{
	float t = 0;
	item_node_t *temp = cart->head;

	while (temp != NULL)
	{
		t += temp->item.quantity * temp->item.unit_price;
		temp = temp->next;
	}
	return t;
}
int last_bill_id()
{
	FILE *fp;
	int id = 0;
	bill_t b;
	int size = sizeof(b);
	fp = fopen("BILL.DAT", "rb");
	if (fp == NULL)
	{
		return id;
	}
	else
	{
		fseek(fp, -size, SEEK_END);
		fread(&b, size, 1, fp);
		id = b.bill_id;
		fclose(fp);
	}
	return id;
}


void display_all_bills()
{
	printf("\n\n\t\t*************BILL*************\n\n");
}


void getTodaysDate(bill_t *b)
{
	time_t t = time(NULL);
	struct tm now = *localtime(&t);
	b->day = now.tm_mday;
	b->month = now.tm_mon + 1;
	b->year = now.tm_year + 1900;
	
}