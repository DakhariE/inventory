//Header file for source files
#ifndef INV_OPERATIONS_H
#define INV_OPERATIONS_H

//Get libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Macro Definitions.
#define ORG_NAME_LEN 50
#define SIZE_LEN 3

//Variables, structs, global variables.
struct tshirt {
	char org_name[ORG_NAME_LEN+1];
	char size[SIZE_LEN+1];
	double price;
	int quantity;
	struct tshirt *next;
};

struct tshirt * add_to_inventory(struct tshirt *inventory);
void search_by_organization(struct tshirt *inventory);
void search_by_size(struct tshirt *inventory);
void print_inventory(struct tshirt *inventory);
void clear_inventory(struct tshirt *inventory);
void change_quan(struct tshirt *inventory);
void help();

#endif
