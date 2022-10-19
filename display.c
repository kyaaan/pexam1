#include "pos.h"


//prints the logo
void printLogo(){
    displayBorder(SCREEN_WIDTH,'=');
    printf("\t\t\t  _  _ ____ ___  ____ _  _ ____ _    ___  . ____\n"); 
    printf("\t\t\t  |\\/| |    |  \\ |  | |\\ | |__| |    |  \\ ' [__ \n");
    printf("\t\t\t  |  | |___ |__/ |__| | \\| |  | |___ |__/   ___]\n"); 
    displayBorder(SCREEN_WIDTH,'=');
}

//prints a border depending on the input symbol
void displayBorder(int iteration, char symbol) {
	for (int x = 0; x < iteration; x++ )
		printf("%c",symbol);
	printf("\n");
}

//calculates the center basedd on the text length
void center(int textLength) {
	for (int x = 0; x < (SCREEN_WIDTH/2)-(textLength/2); x++ )
		printf(" ");
}

//displays text at the center of the console
void displayCenterTitle(char title[]) {
	center(strlen(title));
	printf("%s",title);
}

//displays the menu 
void displayMenu(Products *item, int len) {
    int i = 0;
    system("@cls||clear"); //clears the screen
    printLogo();
    displayCenterTitle("MENU\n");
    displayCenterTitle("* indicates that item has add-ons\n");
    printf("\t\t\tCode\tName\t\t\t\t   Price\n");
    while(i<len)
    {   

        //adds white spaces for layouting purposes
        printf("\t\t\t%s\t%s", item->itemCode,item->name);
        for(int k = 0; k < MAX_MENU_CHARA-strlen(item->name) ; k++) {
			printf(" ");
		}        
        printf("%.2f",item->price);
        
        //prints * symbol if item contains an addon
        if(checkAddOn(item))
            printf("*");
        
        printf("\n");
        i++;
        item++;
    }
    displayBorder(SCREEN_WIDTH,'_');
    printf("\n");
}

//displays the receipt
void displayReceipt(Products *item, int len, float total, float change, float paid) {
    int i = 0;
    system("@cls||clear"); //clears the screen
    printLogo();
    displayCenterTitle("RECEIPT\n");
    printf("\t\t\tCode\tName\t\t\t\t   Qty\tPrice\n\n");
    while(i<len)
    {   
        //skips printing the item if it is not ordered
        if(!item->isOrdered) {
            i++;
            item++;
            continue;
        }
            
        //adds white spaces for layouting purposes
        printf("\t\t\t%s\t%s", item->itemCode,item->name);
        for(int k = 0; k < MAX_MENU_CHARA-strlen(item->name) ; k++) {
			printf(" ");
		}        
        
        //checks if there are any addons
        if(checkAddOn(item)) {
        	bool isIncluded = false;
            for (int j = 0; j < 3; j++) { 
                if(item->addOn[j].isIncluded){
                    printf("%d\t%.2f*",item->qty,(item->price)*item->qty);
                    printf("\n\t\t\t\t\t+%s\t%.2f", item->addOn[j].name,item->addOn[j].price*item->qty);
                    printf("\n\t\t\t\t\t\t\t\t\t%.2f",(item->price+item->addOn[j].price)*item->qty);
    				isIncluded = true;
                }
            }
            if(!isIncluded)
				printf("%d\t%.2f",item->qty, item->price);    
        } else {
            printf("%d\t%.2f",item->qty, item->price);
        }

        printf("\n");
        i++;
        item++;
    }
    displayBorder(SCREEN_WIDTH,'-');
    printf("\t\t\tTotal: %.2f\n", total);
    printf("\t\t\tAmount Paid: %.2f\n", paid);
    printf("\t\t\tChange: %.2f\n", change);

    displayBorder(SCREEN_WIDTH,'_');
    printf("\n");
}

void displayAddOns(Products *item) {
    system("@cls||clear"); //clears the screen
    printLogo();
    displayCenterTitle(item->name);
    displayCenterTitle("\nPlease select and Add on: \n");

    for (int i =0; i < 3; i++) {
        printf("\t\t\t\t[%d]\t%s",i, item->addOn[i].name);
        //adds whitespaces
        for(int k = 0; k < MAX_MENU_CHARA-strlen(item->addOn[i].name) ; k++) {
			printf(" ");
		} 
		printf("%.2f\n",item->addOn[i].price);
    }

    displayBorder(SCREEN_WIDTH,'_');
    printf("\n");
}