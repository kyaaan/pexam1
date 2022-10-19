#include "pos.h"



bool checkAddOn(Products *item){
    for (int i = 0; i < 3; i++) { 
        if(!strcmp(item->addOn[i].name,"~")){
            return false;
        }   
            
    }
    return true;
}

/**
 * This function will access menu.dat and will save it contents into the Product object 
 * @PARAM: Pointer Array (Products Type)
 * Returns: int (menu length)
 * 
 * File content: [column#]Type
 * [0]Item code,[1]Item Name, [2] Category [3]Price,[4]AddOn1,[5]Price,[6]AddOn2,[7]Price[8]AddOn3,[9]Price
 */
int readMenuFile(Products *item) {
    FILE *pfile;
    pfile = fopen("../POS.data", "r");
    char buffer[MAX_CHARA];
    char wordTemp[MAX_CHARA];
    int tempCount = 0;
    int menuLength = 0;
    
    while(fgets(buffer, MAX_CHARA, pfile)) {
        int i = 0;
        int cCount = 0;
        bool run = true;
        int addCount = 0;      
        do{
            wordTemp[tempCount] = buffer[i];
            tempCount++;
            
            if(buffer[i] == ',' || buffer[i] == '\n') {
                wordTemp[tempCount-1] = '\0';
                tempCount = 0;
                
                int choice = cCount;
                if(cCount>3){
                    choice = 4+cCount%2;
                }

                switch (choice)
                { 
                case 0: //itemCode
                    strcpy(item->itemCode,wordTemp); 
                    break;
                case 1: //itemName
                    strcpy(item->name,wordTemp);
                    break;
                case 2: //category
                    strcpy(item->category,wordTemp);    
                    break;
                case 3: //price
                    item->price = strtof(wordTemp,NULL);
                    break;
                case 4: //Addon Name
                    strcpy(item->addOn[addCount].name,wordTemp);
                    break;
                case 5: //Addon Price
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
