/* 
 * File:   StockItem.h
 * Author: Paulo Jorge
 *  */

#ifndef STOCKITEM_H
#define STOCKITEM_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Item type structure defining and storing variables 
 * for a individual stock item.
 */
typedef struct StockItemStruct {
    char *type, *ID, *desc;
    int quantity, price;
}
StockItem;

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
        int price, char *desc);

/**
 * Get method to get type/name of a stock item.
 * 
 * @param  Pointer to stock item containing type.
 * @return Item type/name char. 
 */
char *stockItem_getType(const StockItem *item);

/**
 * Get method to get ID of a stock item.
 * 
 * @param  Pointer to stock item containing ID.
 * @return ID char. 
 */
char *stockItem_getID(const StockItem *item);

/**
 * Get method to get quantity of a stock item.
 * 
 * @param  Pointer to stock item containing quantity.
 * @return Integer quantity of stock. 
 */
int stockItem_getQuantity(const StockItem *item);

/**
 * Get method to get price of a stock item.
 * 
 * @param  Pointer to stock item containing price.
 * @return Item price float in pounds. 
 */
float stockItem_getPrice(const StockItem *item);

/**
 * Get method to get description of a stock item.
 * 
 * @param  Pointer to stock item containing description.
 * @return Description of stock item if item has description or "N/A" if null. 
 */
char *stockItem_getDesc(const StockItem *item);

/**
 * Sale method used to reduce quantity of a stock item by x amount 
 * if stock item has enough quantity within stock for transaction to be 
 * successful.
 * 
 * @param  Pointer to stock item containing quantity.
 * @param  Integer sale quantity to sell.
 * @return 1 if transaction was successful or 0 if not. 
 */
int stockItem_Sell(StockItem *item, const int saleQuantity);

/**
 * Method to print out information about a stock item to the console.
 * 
 * @param  Pointer to stock item to be printed.
 * @return Print of item information.
 */
void stockItem_print(const StockItem *item);

/**
 * Method to free a stock item from memory.
 * 
 * @param Pointer to stock item to which will be freed from memory.
 */
void stockItem_free(StockItem *item);

#ifdef __cplusplus
}
#endif

#endif /* STOCKITEM_H */

