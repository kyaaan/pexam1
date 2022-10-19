#include "pos.h"


void prompt(Products *item, float *pTotal, int len){
    system("@cls||clear");
    displayMenu(item,len);
    displayCenterTitle("TOTAL: ");
    printf("%.2f\n", *pTotal);  
}

/**
 * This function will check the price and qty of the product
 * Responsible for calculations and saving the chosen product to memory
 * 
 * @PARAM: char *pinput, Products *item, float *pTotal, int len, bool *tags
 */
void checkMenu(char *pinput, Products *item, float *pTotal, int len, bool *tags) {    
    prompt(item,pTotal,len);
    Products *pinit = item;
    int i = 0;
    int qty = 0;
    char choice;
    int addOption = 0;

    *tags = false;
    while(i<len)
    {   
        if(!strcmp(item->itemCode, pinput)) {

            //If item is already ordered. It will enter quantity edit mode
            if(item->isOrdered) {
                printf("[Item already Ordered! Entering Quantity change mode...]\n");
                *pTotal -= item->price*item->qty;
                for (int j = 0; j < 3; j++) { 
                    if(item->addOn[j].isIncluded){
                        item->addOn[j].isIncluded = false;
                        *pTotal -= item->addOn[j].price;
                    }   
                }   
            }

            item->isOrdered = true;
            printf("Qty: ");
            scanf("%d", &qty);

            //breaks the loop if quantity is 0
            if(qty<1)
                break;
            
            *tags = false;
            item->qty = qty;
            *pTotal += item->price*qty;

            if(checkAddOn(item)){

                getchar(); //clears input buffer
                printf("Any Add ons?(y/n): ");
                scanf("%c", &choice);

                if(choice == 'n')
                    break;

                displayAddOns(item);
                printf("Option: ");
                scanf("%d", &addOption);

                *pTotal += item->addOn[addOption].price*item->qty;
                item->addOn[addOption].isIncluded = true;
            }
        } 
        i++;
        item++;
    }

    //error checking. prevents user from continuing if there is an error
    if(qty==0){
        item = pinit;
        system("@cls||clear");
        displayMenu(item,len);
        displayCenterTitle("INVALID INPUT!\n");
        *tags = true;
    }
}

/**
 * This function will take the order by entering the product code
 * @PARAM: Pointer Array (Products Type), float Total, int length
 * Returns: bool
 */
bool takeOrder(Products *item, float *pTotal, int len) {
    bool tags = false;
    bool terminate = false;
    
    do {
        char userInput[2];
	    printf("Input Product Code: ");
	    scanf("%s", userInput);
        checkMenu(userInput, item, pTotal, len, &tags);
    } while(tags);

    //asks and terminates the code if user choses to stop ordering
    getchar(); //clear buffer
    char choice;
    prompt(item,pTotal,len);

    printf("Anything else?(y/n): ");
    scanf("%c", &choice);
    if(choice != 'y')
        return false;

    return true;
}

/**
 * This function will return the change after the user inputs an amount
 * @PARAM: Pointer Array (Products Type), float Total, int length
 * Returns: float
 */
float takePayment(Products *item, float *totalBill, float *payment) {
    system("@cls||clear");
    printLogo();
    displayCenterTitle("PAYMENT MODE\nYour total bill is: ");
    printf("%.2f\nEnter Payment: ",*totalBill);

    scanf("%f", payment);
    
    return *payment-*totalBill;
}

int main(void) {
    //intialize all necessary variables
    Products *item;
    item = (Products *)malloc(MAX_ORDER * sizeof(Products));
    float totalBill = 0;
    float amountPaid = 0;
    float change = 0;
    
    int menuLength = readMenuFile(item);

    do{
        prompt(item,&totalBill,menuLength);
    } while (takeOrder(item,&totalBill,menuLength));

    change = takePayment(item, &totalBill, &amountPaid);
    displayReceipt(item,menuLength,totalBill,change,amountPaid);

    free(item); 
    return 0;
}