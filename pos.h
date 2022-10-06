#ifndef POS_H
#define POS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
    float price;
    AddOns addOn[MAX_ADDON];  
}Products;

int readMenuFile(Products *item);

#endif