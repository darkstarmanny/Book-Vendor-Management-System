#ifndef VENDOR_H
#define VENDOR_H
typedef struct Vendor
{
	int vendor_id;
	char company[60];
	char name[60];
	char lastname[60];
	char email[60];
	char contactNo[60];
	char accountNo[60];
	float discount;
}vendor_t;

void write_vendor_in_file(vendor_t *vend);
void read_vendor_from_file();
//void find_vendor(char *); 
void display_vendor(vendor_t *vend);
int find_vendor_by_id(int id, vendor_t *vend);
int last_vendor_id();
#endif