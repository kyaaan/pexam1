#include "pos.h"

void displayMenu(Products *item, int len) {
    int i = 0;

    printf("\e[1;1H\e[2J"); //clears the screen
    printf("Code\tName\tPrice\n");
    while(i<len)
    {
        printf("%s\t%s\t%.2f\n", item->itemCode, item->name, item->price);
        
        for (int j = 0; j < 3; j++)
        {
            printf("\n\t\tAddons [%d]: %s\t%.2f\t%d\n", j+1, item->addOn[j].name, item->addOn[j].price, item->addOn[j].isIncluded);
        }
            
        i++;
        item++;
    }
}

int main(void) {
    //intialize all necessary variables

    Products *item;
    item = (Products *)malloc(MAX_ORDER * sizeof(Products));
    
    int menuLength = readMenuFile(item);
    displayMenu(item, menuLength); 

    return 0;
}