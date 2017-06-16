#include<stdio.h>
#include<conio.h>
#include<string.h>
#include"vendor.h"

void input_vendor(vendor_t *vend)
{
	printf("\n**Enter Vendor Details**\n");
	printf("\nEnter id: ");
	scanf("%d", &vend->vendor_id);
	fflush(stdin);
	printf("\nCompany Name: ");
	scanf("%s", vend->company);
	fflush(stdin);
	printf("\nName: ");
	scanf("%s", vend->name);
	fflush(stdin);
	printf("\nLast Name: ");
	scanf("%s", vend->lastname);
	fflush(stdin);
	printf("\nEnter Email Id: ");
	scanf("%s", vend->email);
	fflush(stdin);
	printf("\nEnter Contact no: ");
	scanf("%s", vend->contactNo);
	fflush(stdin);
	printf("\nEnter account no: ");
	scanf("%s", vend->accountNo);
	fflush(stdin);
	printf("\nEnter Discount: ");
	scanf("%f", &vend->discount);
}
void write_vendor_in_file(vendor_t *vend)
{
	FILE *fp;
	input_vendor(vend);

	fp = fopen("VENDOR.DAT", "ab");
	if (fp == NULL)
	{
		printf("Unable to open file \n");
	}
	else
	{
		fwrite(vend, sizeof(*vend), 1, fp);
	}
	fclose(fp);
}
void read_vendor_from_file()
{
	FILE *fp;
	vendor_t c;

	fp = fopen("VENDOR.DAT", "rb");

	if (fp == NULL)
	{
		printf("unable to open file \n");
	}
	else
	{
		printf("\n------------------------------------------------\n");
		printf("\nVendor id:  \tVendor Name: \tVendor last name:\tEmail ID: \tContact no: \tDiscount: \n");
		while (fread(&c, sizeof(c), 1, fp) != NULL)
		{
			display_vendor(&c);
		}
		printf("\n------------------------------------------------\n");
	}
}
//void find_vendor(char *)
//{
//
//}
void display_vendor(vendor_t *vend)
{
	printf("\n %d \t\t%s\t\t%s\t\t\t%s\t\t%s\t\t%f \n", vend->vendor_id, vend->name, vend->lastname, vend->email, vend->contactNo, vend->discount);
}
int find_vendor_by_id(int id, vendor_t *vend)
{
	FILE *fp;
	vendor_t v;
	int flag = 0;
	fp = fopen("VENDOR.DAT", "rb");
	if (fp == NULL)
	{
		printf("unable to open file \n");
		return flag;
	}
	else
	{
		while (fread(&v, sizeof(v), 1, fp) != 0)
		{
			if (v.vendor_id == id)
			{
				flag = 1;
				*vend = v;
				break;
			}
		}
	}
	return flag;
}
int last_vendor_id()
{
	FILE *fp;
	int id = 0;
	vendor_t v;
	int size = sizeof(v);
	fp = fopen("VENDOR.DAT", "rb");
	if (fp == NULL)
	{
		return id;
	}
	else
	{
		fseek(fp, -size, SEEK_END);
		fread(&v,size,1,fp);
		id = v.vendor_id;
		fclose(fp);
	}
	return id;
}