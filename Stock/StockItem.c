/* 
 * File:   StockItem.c
 * Author: Paulo Jorge.
 */

#include <stdio.h>
#include <stdlib.h>

#include "StockItem.h"
#include "Date.h"

/**
 * Method to allocate memory for a new stock item containing information 
 * about itself. Or generates error message if memory allocation fails
 * and terminates program.
 * 
 * @param  Char type/name of item.
 * @param  Char unique ID.
 * @param  Integer quantity of item in stock.
 * @param  Integer price of item in pennies.
 * @param  Char item description.
 * @return Pointer to newly created stock item.
 */
StockItem* stockItem_new(char *type, char *ID, int quantity, 
        int price, char *desc) {
    // Allocate item to memory
    StockItem *item = (StockItem*)malloc(sizeof(StockItem));
    // Null check memory allocation
    if (!item) {
        fprintf(stderr, "Error: Unable to allocate memory in "
                "stockItem_new().\n");
        exit(EXIT_FAILURE);
    }
    
    // Pass in stock item information
    item->type     = type;
    item->ID       = ID;
    item->quantity = quantity;
    item->price    = price;
    item->desc     = desc;
                
    return item;
}

/**
 * Get method to get type/name of a stock item.
 * 
 * @param  Pointer to stock item containing type.
 * @return Item type/name char. 
 */
char *stockItem_getType(const StockItem *item) {
    return item->type;
}

/**
 * Get method to get ID of a stock item.
 * 
 * @param  Pointer to stock item containing ID.
 * @return ID char. 
 */
char *stockItem_getID(const StockItem *item) {
    return item->ID;
}

/**
 * Get method to get quantity of a stock item.
 * 
 * @param  Pointer to stock item containing quantity.
 * @return Integer quantity of stock. 
 */
int stockItem_getQuantity(const StockItem *item) {
    return item->quantity;
}

/**
 * Get method to get price of a stock item in pounds.
 * 
 * @param  Pointer to stock item containing price integer in pennies.
 * @return Item price float in pounds. 
 */
float stockItem_getPrice(const StockItem *item) {
    int pennies = item->price;
    // Get total pounds
    float pounds = pennies / 100;
    // Get total pennies
    pennies = pennies % 100;
    
    // Return pounds + decimal value of pennies
    return (pounds + ((float)pennies / 100));
}

/**
 * Get method to get description of a stock item.
 * 
 * @param  Pointer to stock item containing description.
 * @return Description of stock item if item has description or "N/A" if null. 
 */
char *stockItem_getDesc(const StockItem *item) {
    // If item doesn't have description output N/A
    return item->desc ? item->desc : "N/A";
}

/**
 * Sale method used to reduce quantity of a stock item by x amount 
 * if stock item has enough quantity within stock for transaction to be 
 * successful.
 * 
 * @param  Pointer to stock item containing quantity.
 * @param  Integer sale quantity to sell.
 * @return 1 if transaction was successful or 0 if not. 
 */
int stockItem_Sell(StockItem *item, const int saleQuantity) {
    int currentQuantity = stockItem_getQuantity(item);
    // If transaction would be successful reduce quantity and return 1 for true
    if ((currentQuantity - saleQuantity) >= 0) {
        item->quantity = (currentQuantity - saleQuantity);
        return 1;
    }
    else 
        return 0;
}

/**
 * Method to print out information about a stock item.
 * 
 * @param  Pointer to stock item to be printed.
 * @return Print of item information.
 */
void stockItem_print(const StockItem *item) { 
    printf("\nType:              %s\n"
             "ID:                %s\n"
             "Quantity in stock: %d\n"
             "Price Per Item:    £%.2f\n"
             "Description:       %s\n",
             stockItem_getType(item), 
             stockItem_getID(item), 
             stockItem_getQuantity(item), 
             stockItem_getPrice(item), 
             stockItem_getDesc(item));
}

/**
 * Method to free a stock item from memory.
 * 
 * @param Pointer to stock item to which will be freed from memory.
 */
void stockItem_free(StockItem *item) {
    free(item);
}