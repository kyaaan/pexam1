#ifndef POS_H
#define POS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SCREEN_WIDTH 100
#define MAX_MENU_CHARA 35

#define MAX_CHARA 256
#define MAX_ORDER 1000
#define MAX_ADDON 3


typedef struct AddOns{
    char name[MAX_CHARA];
    float price;
    bool isIncluded;
}AddOns;

typedef struct Products{
    char itemCode[3];
    char name[MAX_CHARA];
    char category[MAX_CHARA];
    float price;
    AddOns addOn[MAX_ADDON];
    bool isOrdered;
    int qty;
}Products;


//function prototypes
int readMenuFile(Products *item);
bool checkAddOn(Products *item);
void printLogo();
void displayBorder(int iteration, char symbol);
void displayMenu(Products *item, int len);
void displayReceipt(Products *item, int len, float total, float change, float paid);
void displayCenterTitle(char title[]);
void displayAddOns(Products *item);
void center(int textLength);

#endif