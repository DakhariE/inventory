#include "inv_operations.h"
#include "readline.h"
//Functions to be used in main.
void help() {
	printf("List of operation codes:\n");
	printf("\t'a' for adding an item to the inventory;\n");
	printf("\t'o' for searching by organization;\n");
	printf("\t's' for searching by size;\n");
    printf("\t'c' for changing quantity of an item;\n");
	printf("\t'p' for printing the inventory;\n");
	printf("\t'q' for quit.\n");
}


struct tshirt * add_to_inventory(struct tshirt *inventory) {

	//Initiate new shirt variables.
	char tempName[51];
	char tempSize[4];
	double tempPrice;
	int tempQuan,compare_size,compare_name;

	struct tshirt *p;
	struct tshirt *prev;
    //Ask user for data about new shirt.
    printf("\nEnter the name of the organization: ");
    read_line(tempName,51);
    printf("\nEnter the size of the shirt: ");
    scanf("%s",tempSize);
    int flag = 0;
    const char * Sizes[8] = {"XS","S","M","L","XL","XXL"};
    SIZE:while(flag == 0){
        for(int v = 0;v < 6;v++)
        {
            int valid_size = strcmp(Sizes[v],tempSize);
            if (valid_size == 0){
                flag = 1;
                goto SIZE;
            }
        }
        printf("\nPlease enter a valid size (XS-XXL): ");
        scanf("%s",tempSize);
    }

    // Code to check if tshirt already existing
    for(p=inventory;p!=NULL;p=p->next){
        compare_size = strcmp(p->size,tempSize);
        compare_name = strcmp(p->org_name,tempName);
        if(compare_size == 0 && compare_name == 0)
        {
            printf("!! Shirt Already exists !!\n");
            return inventory;
        }
    }
    //Still asking for data.
    printf("\nEnter the price and quantity: ");
    scanf("%lf %d", &tempPrice,&tempQuan);

    //struct tshirt *new_shirt;

    //Set input values as shirt attributes
    struct tshirt *new_shirt = (struct tshirt*)malloc(sizeof(struct tshirt));
    strcpy(new_shirt->org_name, tempName);
    strcpy(new_shirt->size, tempSize);
    new_shirt->price = tempPrice;
    new_shirt->quantity = tempQuan;
    new_shirt->next = NULL;
    //Check to see inventory is empty.
    if(inventory == NULL)
    {
        inventory = new_shirt;
    }
    else{
        // Add tshirt to end of inventory list.
        for(p=inventory,prev = NULL;p!=NULL ;prev = p,p = p->next)
        {
           compare_name = strcmp(tempName,p->org_name);
           compare_size = strcmp(tempSize,p->size);
           if(compare_name == 0 && compare_size < 0)
           {
                if(prev == NULL){
                    inventory = new_shirt;
                    new_shirt->next = p;
                    break;
                }
                else{
                    prev->next = new_shirt;
                    new_shirt->next = p;
                    break;
                }
           }
           if(compare_name < 0)
           {
               if(prev == NULL){
                    inventory = new_shirt;
                    new_shirt->next = p;
                    break;
                }
                else{
                    prev->next = new_shirt;
                    new_shirt->next = p;
                    break;
                }
           }
           else{
                if(p->next == NULL){
                    p->next = new_shirt;
                break;
               }
               continue;
           }
        }

   }
    return inventory;
}

void search_by_organization(struct tshirt *inventory) {
    //Initiate variables for checking if orgName matches.
    char orgName[51];
    int i =0;
    int compare;
    struct tshirt *p;
	printf("\nWhat organization are you looking for? ");
	read_line(orgName,51);
    //Print orgNames matching input.
	for(p=inventory;p!=NULL;p=p->next)
	{
        compare = strcmp(p->org_name,orgName);
        if(compare == 0)
        {
        i++;
        }
	}
	//If theres nothing equal in list then print not found
	if (i==0)
    {
         printf("\n!No shirts of this organization available!");
    }
    else{
    printf("\n|----------------------------------------------------|-----|------------|-----------|\n");
	printf("| Student organization                               | Sz. |      Price |      Qty. |\n");
	printf("|----------------------------------------------------|-----|------------|-----------|\n");
        for(p=inventory;p!=NULL;p=p->next)
        {
        compare = strcmp(p->org_name,orgName);
        if(compare == 0)
            {
            printf("| %-50s | %-3s |   %5.2f        %4d   \n", p->org_name, p->size, p->price, p->quantity);
            i++;
            }
        }
        printf("|----------------------------------------------------|-----|------------|-----------|\n");
    }
}

void search_by_size(struct tshirt *inventory) {
    //Initiate variables for checking if size matches.
    char Tsize[4];
    int i=0;
    int compare;
    struct tshirt *p;
	printf("\nWhat size are you looking for? (XS-XXL)");
    scanf("%s", Tsize);
    //This checks if size is valid

    int flag = 0;
    const char * Sizes[8] = {"XS","S","M","L","XL","XXL"};
    TSIZE:while(flag == 0){
        for(int v = 0;v < 6;v++)
        {
            int valid_size = strcmp(Sizes[v],Tsize);
            if (valid_size == 0){
                flag = 1;
                goto TSIZE;
            }
        }
        printf("\nPlease enter a valid size (XS-XXL): ");
        scanf("%s",Tsize);
    }

    //Check for any sizes
	for(p = inventory;p!=NULL;p = p->next)
    {
        compare = strcmp(p->size,Tsize);
        if(compare == 0)
        {
            i++;
        }
    }

    //If theres nothing equal in list then print not found
	if (i==0){
        printf("No shirts of this size available!");
	}
    else{
    printf("\n|----------------------------------------------------|-----|------------|-----------|\n");
	printf("| Student organization                               | Sz. |      Price |      Qty. |\n");
	printf("|----------------------------------------------------|-----|------------|-----------|\n");
	for(p = inventory;p!=NULL;p = p->next)
    {
        compare = strcmp(p->size,Tsize);
        if(compare == 0)
        {
            printf("| %-50s | %-3s |   %5.2f        %4d   \n", p->org_name, p->size, p->price, p->quantity);
        }
    }
    printf("|----------------------------------------------------|-----|------------|-----------|\n");
    }

}

void print_inventory(struct tshirt *inventory) {

	//Temp pointer
	struct tshirt *p;
	if (inventory==NULL)
        {
            printf("No t-shirts in inventory");
        }
    else{
	printf("\n|----------------------------------------------------|-----|------------|-----------|\n");
	printf("| Student organization                               | Sz. |      Price |      Qty. |\n");
	printf("|----------------------------------------------------|-----|------------|-----------|\n");

    //Print every node.
	for(p=inventory ; p!=NULL; p=p->next)
    {
        printf("| %-50s | %-3s |   %5.2f        %4d   \n", p->org_name, p->size, p->price, p->quantity);
    }
    printf("|----------------------------------------------------|-----|------------|-----------|\n");
    }
}

void change_quan(struct tshirt *inventory) 
{
    struct tshirt *p;
    char brand[50];
    char Csize[4];
    int Nquant;
    int found = 0;
    if(inventory == NULL)
    {
        printf("Nothing in inventory to edit!");
    }
    else
    {
    printf("Enter the name of the Brand: ");
    scanf("%s", brand);
    printf("Enter the size to modify: ");
    scanf("%s", Csize);

    for(p = inventory;p!=NULL;p = p->next)
    {
        int compare_brand = strcmp(p->org_name, brand);
        int compare_size = strcmp(p->size,Csize);
    
        if(compare_size == 0 && compare_brand == 0) 
        {
            printf("\nCurrent Qty: %d", p->quantity);
            printf("\nWhat is the new quantity? ");
            scanf("%d", &Nquant);
            p->quantity = Nquant;
            printf("New quantity for %s is %d", p->org_name, p->quantity);
            found = 1;
            break;
        }
    }
    if(found==0)
    printf("Item not in inventory!");
    }
}

void clear_inventory(struct tshirt *inventory) {
    //Temp pointer
    struct tshirt *temp;
    temp = inventory;
    //Delete every tshirt in inventory.
    while(inventory!=NULL)
    {
        temp = temp->next;
        free(inventory);
        inventory = temp;
    }
}