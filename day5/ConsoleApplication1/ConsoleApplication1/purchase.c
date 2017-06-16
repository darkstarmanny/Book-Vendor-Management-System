#include<stdio.h>
#include<conio.h>
#include<string.h>
#include"purchase.h"
#include"vendor.h"

void input_purchase_order(porder_t *po)
{
	porder_t p;
	int id, check;
	vendor_t vend;
	float temp;
	printf("\nEnter Vendor id:");
	scanf("%d", &id);
	;
	if (find_vendor_by_id(id, &vend)==1)
	{
		po->po_id = last_po_id() + 1;
		po->vendor_id = vend.vendor_id;
		strcpy(po->v_company, vend.company);
		po->discount = vend.discount;
		printf("\nEnter product name: ");
		scanf("%s",po->item.product_Name);
		printf("\nEnter product quantity: ");
		scanf("%d", &po->item.quantity);
		printf("\nEnter product price: ");
		scanf("%f", &po->item.unit_price);

		po->total = ((po->item.quantity)*(po->item.unit_price));
		temp = po->total*(vend.discount) / 100;
		po->discount = po->total - temp;
		po->status = RAISED;

	}
	else
	{
		printf("\nVendor is not Registered,Please First Register\n");
	}
}
void write_porder_in_file(porder_t *po)
{
	FILE *fp;
	input_purchase_order(po);

	fp = fopen("PURCHASE.DAT", "ab");
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
void read_porder_from_file()
{
	FILE *fp;
	porder_t c;

	fp = fopen("PURCHASE.DAT", "rb");

	if (fp == NULL)
	{
		printf("unable to open file \n");
	}
	else
	{
		printf("\n------------------------------------------------\n");
		printf("\nPurchase order id: \tCompany: \tProduct Name:\tQuantity: \tUnit Price: \tTotal : \tDiscount: \tStatus: \n");
		while (fread(&c, sizeof(c), 1, fp) != NULL)
		{
			display_porder(&c);
		}
		printf("\n------------------------------------------------\n");
	}
}
void display_porder(porder_t *po)
{
	printf("\n%d \t\t\t%s\t%s\t\t%d\t\t %f\t%f\t%f\t%d\n", po->po_id,po->v_company,po->item.product_Name,po->item.quantity,po->item.unit_price,po->total,po->discount,po->status);
}
int last_po_id()
{
	FILE *fp;
	int id = 0;
	porder_t v;
	int size = sizeof(v);
	fp = fopen("PURCHASE.DAT", "rb");
	if (fp == NULL)
	{
		return id;
	}
	else
	{
		fseek(fp, -size, SEEK_END);
		fread(&v, size, 1, fp);
		id = v.po_id;
		fclose(fp);
	}
	return id;
}
int find_purchase_order_by_name(char *purchase, porder_t *po_out)
{
	FILE *fp;
	porder_t v;
	int flag = 0;
	fp = fopen("PURCHASE.DAT", "rb");
	if (fp == NULL)
	{
		printf("unable to open file \n");
		return flag;
	}
	else
	{
		while (fread(&v, sizeof(v), 1, fp) != 0)
		{
			if (strcmp(purchase,v.item.product_Name) == 0)
			{
				flag = 1;
				*po_out = v;
				break;
			}
		}
	}
	return flag;
}
//void received_order()
//{
//
//}