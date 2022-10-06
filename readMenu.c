#include "pos.h"

/**
 * This function will access menu.dat and will save it contents into the Product object 
 * @PARAM: Pointer Array (Products Type)
 * Returns: int (menu length)
 * 
 * File content: [column#]Type
 * [0]Item code,[1]Item Name,[2]Price,[3]AddOn1,[4]Price,[5]AddOn2,[6]Price[7]AddOn3,[8]Price
 */

int readMenuFile(Products *item) {
    FILE *pfile;
    pfile = fopen("POS.menu", "r");
    char buffer[MAX_CHARA];
    char wordTemp[MAX_CHARA];
    int tempCount = 0;
    int menuLength = 0;
    
    while(fgets(buffer, MAX_CHARA, pfile)) {
        int i = 0;
        int cCount = 0;
        int addCount = 0;
        bool run = true;      
        do{
            wordTemp[tempCount] = buffer[i];
            tempCount++;
            
            if(buffer[i] == ',' || buffer[i] == '\n') {
                wordTemp[tempCount-1] = '\0';
                tempCount = 0;

                
                int choice = cCount;
                if(cCount>2){
                    choice = 4-cCount%2;
                }
                
                switch (choice)
                { 
                case 0: //itemCode
                    strcpy(item->itemCode,wordTemp); 
                    break;
                case 1: //itemName
                    strcpy(item->name,wordTemp);
                    break;
                case 2: //price
                    item->price = strtof(wordTemp,NULL);
                    break;
                case 3: //Addon Name
                    strcpy(item->addOn[addCount].name,wordTemp);
                    break;
                case 4: //Addon Price
                    item->addOn[addCount].price = strtof(wordTemp,NULL);
                    item->addOn[addCount++].isIncluded = false;
                    break;
                default:
                    break;
                }
                cCount++; 
            }
            i++;
        }while(buffer[i]);
        item++;
        menuLength++;
    }

    fclose(pfile);
    return menuLength;
}
