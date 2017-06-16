#include<stdio.h>
#include<conio.h>
#include<string.h>
#include"customer.h"


void input_customer(customer_t *cust)
{
	printf("\n**Enter Customer Details**\n");
	printf("\nEnter Name: ");
	scanf("%s", cust->name);
	printf("\nLast Name: ");
	scanf("%s", cust->lastname);
	printf("\nEnter Email Id: ");
	scanf("%s", cust->email);
	printf("\nEnter Contact no: ");
	scanf("%s", cust->contactno);
}
void write_customer_in_file(customer_t *cust)
{
	FILE *fp;
	input_customer(cust);

	fp = fopen("CUSTOMER.DAT", "ab");
	if (fp == NULL)
	{
		printf("Unable to open file \n");
	}
	else
	{
		fwrite(cust, sizeof(*cust), 1, fp);
	}
	fclose(fp); 
}
void read_customer_from_file()
{
	FILE *fp;
	customer_t c;

	fp = fopen("CUSTOMER.DAT", "rb");

	if (fp == NULL)
	{
		printf("unable to open file \n");
	}
	else
	{
		printf("\n------------------------------------------------\n");
		printf("\nCustomer Name:  \tCustomer last Name: \tEmail ID: \tContact no:  \n");
		while (fread(&c, sizeof(c), 1, fp) != NULL)
		{
			display_customer(&c);
		}
		printf("\n------------------------------------------------\n");
	}
}
int find_customer(char *contactno, customer_t *cu)
{
	FILE *fp;
	customer_t cust;
	int flag = 0;
	fp = fopen("CUSTOMER.DAT","rb");
	if (fp== NULL)
	{
		printf("unable to open file \n");
		return flag;
	}
	else
	{
		while (fread(&cust, sizeof(cust), 1, fp) != 0)
		{
			if (strcmp(cust.contactno,contactno)==0)
			{
				flag = 1;
				*cu=cust;
				break;
			}
		}
	}
	return flag;

}
void display_customer(customer_t *cust)
{
	printf("\n%s \t\t\t%s\t\t\t%s\t\t%s \n", cust->name, cust->lastname,cust->email,cust->contactno);
}
