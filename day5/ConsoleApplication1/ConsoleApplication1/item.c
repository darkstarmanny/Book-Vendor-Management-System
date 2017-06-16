
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include"item.h"

void input_items(item_t *item)
{
	printf("\n**Enter Item Details**\n");
	printf("\nEnter Item ID: ");
	scanf("%d", &item->itemid);
	printf("\nProduct Name: ");
	scanf("%s", item->product_Name);
	printf("\nEnter Product Description: ");
	scanf("%s", item->product_Description);
	printf("\nEnter Quantity: ");
	scanf("%d",& item->quantity);
	printf("\nEnter Unit Price: ");
	scanf("%f", &item->unit_price);
}
void write_item_in_file(item_t *item)
{
	FILE *fp;
	input_items(item);

	fp = fopen("STOCK.DAT", "ab");
	if (fp == NULL)
	{
		printf("Unable to open file \n");
	}
	else
	{
		fwrite(item, sizeof(*item), 1, fp);
	}
	fclose(fp);
}
void read_item_from_file()
{
	FILE *fp;
	item_t c;

	fp = fopen("STOCK.DAT", "rb");

	if (fp == NULL)
	{
		printf("unable to open file \n");
	}
	else
	{
		printf("\n------------------------------------------------\n");
		printf("\nItem id: \tProduct Name: \tProduct Description:\tQuantity: \tUnit Price:  \n");
		while (fread(&c, sizeof(c), 1, fp) != NULL)
		{
			display_item(&c);
		}
		printf("\n------------------------------------------------\n");
	}
}
int find_item_by_name(char *pname, item_t *itout)
{
	FILE *fp;
	item_t v;
	int flag = 0;
	fp = fopen("STOCK.DAT", "rb");
	if (fp == NULL)
	{
		printf("unable to open file \n");
		return flag;
	}
	else
	{
		while (fread(&v, sizeof(v), 1, fp) != 0)
		{
			if (strcmp(v.product_Name, pname) == 0)
			{
				flag = 1;
				*itout = v;
				break;
			}
		}
	}
}
void display_item(item_t *item)
{
	printf("\n %d\t\t%s\t\t%s\t\t\t%d\t\t%f \n",item->itemid,item->product_Name,item->product_Description,item->quantity,item->unit_price );
}
int last_item_id()
{
	FILE *fp;
	int id = 0;
	item_t v;
	int size = sizeof(v);
	fp = fopen("STOCK.DAT", "rb");
	if (fp == NULL)
	{
		//printf("Cannot open file \n");
		return id;
	}
	else
	{
		fseek(fp, -size, SEEK_END);
		fread(&v, size, 1, fp);
		id = v.itemid;
		fclose(fp);
	}
	return id;
}