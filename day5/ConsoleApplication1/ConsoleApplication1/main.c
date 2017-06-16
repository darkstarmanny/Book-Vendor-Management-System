#include<stdio.h>
#include<conio.h>
#include<string.h>
#include"customer.h"
#include"vendor.h"
#include"item.h"
#include"purchase.h"
#include"list.h"
#include"bill.h"

enum operation{EXIT=0,CUSTOMER_M,PURCHASE_M,ITEM_M,SALES_M};
int operation_menu()
{
	int choice;
	printf("0.EXIT\n1.Customer\n2.Purchase Manager\n3.Item Manager\n4.Sales Manager\nEnter choice : ");
	scanf("%d", &choice);
	return choice;
}

enum submenu_cust {ADD_C=1,LIST_C};
int suboperation_cust()
{
	int choice;
	printf("\n0.EXIT\n1.Add New Customer\n2.List of all Customer\nEnter choice : ");
	scanf("%d", &choice);
	return choice;
}

enum submenu_purchase_manager { ADD_V=1, SHOW_V,CREATE_P,SHOW_P };
int suboperation_purchase_manager()
{
	int choice;
	printf("\n0.EXIT\n1.Add New Vendor\n2.Show all Vendor\n3.Create New Purchase Order\n4.Show all purchase Order\nEnter choice : ");
	scanf("%d", &choice);
	return choice;
}

enum submenu_item_manager { ADD_I= 1, DISP_I };
int suboperation_item_manager()
{
	int choice;
	printf("\n0.EXIT\n1.Add New Item\n2.Disp all Items\nEnter choice : ");
	scanf("%d", &choice);
	return choice;
}

enum submenu_sales_manager { SALE = 1, BILL };
int suboperation_sale_manager()
{
	int choice;
	printf("\n0.EXIT\n1.Sale\n2.Generate Bill\nEnter choice : ");
	scanf("%d", &choice);
	return choice;
}

enum submenu_sale { ADD_S = 1, SHOW_SS };
int suboperation_sale()
{
	int choice;
	printf("\n0.EXIT\n1.Add item in cart\n2.Show cart List\nEnter choice : ");
	scanf("%d", &choice);
	return choice;
}

enum submenu_generate_bill { SALE_GS = 1, DISP_S };
int suboperation_generate_bill()
{
	int choice;
	printf("\n0.EXIT\n1.Show current Bill\n2.Display all Bill\nEnter choice : ");
	scanf("%d", &choice);
	return choice;
}

int main()
{
	int ch;
	int a,as;
	customer_t cust;
	vendor_t vend;
	item_list_t list,cart;
	init_head(&list);
	init_head(&cart);
	porder_t po;
	bill_t b;
	load_items_from_stock_to_link_list(&list);
	do
	{

		ch = operation_menu();

		switch (ch)
		{
		case EXIT:
			break;
		case CUSTOMER_M:
			do
			{

				as = suboperation_cust();
				switch (as)
				{
				case EXIT:
					break;
				case ADD_C:
					write_customer_in_file(&cust);
					break;
				case LIST_C:
					read_customer_from_file();
					break;
				}
			} while (as != 0);
			break;


			case PURCHASE_M:
				do
				{
					as = suboperation_purchase_manager();
					switch (as)
					{
					case EXIT:
						break;
					case ADD_V:
						write_vendor_in_file(&vend);
						break;
					case SHOW_V:
						read_vendor_from_file();
						break;
					case CREATE_P:
						write_porder_in_file(&po);
						break;
					case SHOW_P:
						read_porder_from_file();
						break;
					}
				} while (as != 0);
				break;

			case ITEM_M:
				do
				{
					as = suboperation_item_manager();
					switch (as)
					{
					case EXIT:
						break;
					case ADD_I:
						input_itm(&list);
						break;
					case DISP_I:
						display_list(&list);
						break;
					}
				} while (as != 0);
				write_link_list_in_stock(&list);
				break;

			case SALES_M:
				do
				{
					as = suboperation_sale_manager();
					switch (as)
					{
					case EXIT:
						break;
					case SALE:
						do{
							a = suboperation_sale();
							switch (a)
							{
							case EXIT:
								break;
							case ADD_S:
								printf("\nAdd Item in the Cart");
								display_list(&list);
								add_items_in_cart_list(&list, &cart);
								break;
							case SHOW_SS:
								printf("\nShow Cart List");
								display_cart_list(&cart);
								break;
							}
						} while (a != 0);
						break;
					case BILL:
						do{
							a = suboperation_generate_bill();
							switch (a)
							{
							case EXIT:
								break;
							case SALE_GS:
								printf("\nShow Current Bill");
								generate_bill(&b, &cart);
								break;
							case DISP_S:
								printf("\nDisplay all Bill");
								read_bill_from_file();
								break;
							}
						} while (a != 0);
						break;
					}
				} while (as != 0);
				break;
		}
	} while (ch != 0);
	
	return 0;
}

