/* 
 * File:   Sales.h
 * Author: Paulo Jorge
 */

#ifndef SALES_H
#define SALES_H

#include "StockItem.h"
#include "Date.h"
#include "Inventory.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Node structure defining and containing information about a sale.
 */
typedef struct SalesNodeStruct {
    StockItem *item;
    Date *date;
    char *ID;
    int quantity;
    struct SalesNodeStruct* next;
}
SalesNode;

/**
 * Sales type structure defining and containing node information.
 */
typedef struct SalesStruct {
    SalesNode* first;
    SalesNode* last;
}
Sales;

/**
 * Definition for iterator type used to iterate through sales list nodes.
 */
typedef SalesNode* SalesIterator;

/**
 * Method to get the first node in a sales list.
 * 
 * @param  Pointer to sales to get first node from.
 * @return Node of first item in sales.
 */
static inline SalesIterator sales_first(const Sales *sales) {
    return sales->first;
}

/**
 * Method to get the last node in a sales list.
 * 
 * @param  Pointer to sales to get last node from.
 * @return Node of last item in sales.
 */
static inline SalesIterator sales_last(const Sales *sales) {
    return sales->last;
}

/**
 * Method to get the next node.
 * 
 * @param  Current value of iterator.
 * @return Next node in sales list.
 */
static inline SalesIterator sales_iteratorNext
    (const SalesIterator i) {
    return i->next;
}

/**
 * Method to get the current node of the iterator.
 * 
 * @param  Iterator to be checked.
 * @return Current node of iterator.
 */
static inline SalesIterator sales_iteratorGetCurrent
    (const SalesIterator i) {
    return i;
}

/**
 * Method to allocate memory for a new sales list of sales. Or 
 * generates error message if memory allocation fails and terminates program.
 * 
 * @return Pointer to newly created sales.
 */
Sales* sales_new();

/**
 * Method to append a new sale to the tail of a sales list. 
 * Or generates error message if memory allocation fails and terminates 
 * program.
 * 
 * @param Pointer to sales list of which will be appended to.
 * @param Pointer to stock item sold.
 * @param Pointer to date containing date.
 * @param Char ID of stock item sold.
 * @param Integer Quantity of number of items sold.
 */
void sales_add(Sales* sales, Inventory* inventory, Date *date, char *ID, 
        int quantity);

/**
 * Method to append a new sale to the head of a sales list. 
 * Or generates error message if memory allocation fails and terminates 
 * program.
 * 
 * @param Pointer to sales list of which will be appended to.
 * @param Pointer to stock item sold.
 * @param Pointer to date containing date.
 * @param Char ID of stock item sold.
 * @param Integer Quantity of number of items sold.
 */
void sales_insert(Sales* sales, Inventory* inventory, Date *date, char *ID, 
        int quantity);

/**
 * Method to return the number of sales currently stored in a sales list.
 * 
 * @param  Pointer to the sales list of which will be checked.
 * @return Integer value of number of elements within sales.
 */
int sales_count(const Sales* sales);

/**
 * Method to remove a sale at the tail of a sales list.
 * 
 * @param  Pointer to the sales list where the tail will be removed.
 */
void sales_removeTail(Sales* sales);

/**
 * Method to remove a sale at the head of a sales list.
 * 
 * @param  Pointer to the sales list where the head will be removed.
 */
void sales_removeHead(Sales* sales);

/**
 * Method to clear all the elements within a sales list structure.
 *  
 * @param Pointer to sales list to be cleared.
 */
void sales_clear(Sales* sales);

/**
 * Get method to get ID of a sales node.
 * 
 * @param  Pointer to sales node containing ID.
 * @return ID char. 
 */
char *sales_getID(const SalesNode* node);

/**
 * Get method to get quantity of a sales node.
 * 
 * @param  Pointer to sales node containing quantity.
 * @return Integer quantity value. 
 */
int sales_getQuantity(const SalesNode* node);

/**
 * Get method to get total cost of a sales node.
 * 
 * @param  Pointer to sales node containing quantity and
 *         reference to stock item sold.
 * @return Float total cost value in pounds. 
 */
float sales_getCost(const SalesNode* node);

/**
 * Method to print a specific sales node to the console.
 * 
 * @param Pointer to sales node to be printed.
 */
void sales_printSale(const SalesNode *node);

/**
 * Method to print all elements within a sales list to the console.
 * 
 * @param Pointer to sales list to be printed.
 */
void sales_print(const Sales* sales);

/**
 * Method to free sales list from memory.
 * 
 * @param Pointer to sales list to which will be freed from memory.
 */
void sales_free(Sales* sales);

#ifdef __cplusplus
}
#endif

#endif /* SALES_H */

