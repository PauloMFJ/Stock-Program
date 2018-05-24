/* 
 * File:   Inventory.h
 * Author: Paulo Jorge
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include "StockItem.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Node structure defining and containing information about a stock item in
 * the inventory.
 */
typedef struct InventoryNodeStruct {
    StockItem *item;
    struct InventoryNodeStruct* next;
}
InventoryNode;

/**
 * Inventory type structure defining and containing node information.
 */
typedef struct InventoryStruct {
    InventoryNode* first;
    InventoryNode* last;
}
Inventory;

/**
 * Definition for iterator type used to iterate through inventory nodes.
 */
typedef InventoryNode* InventoryIterator;

/**
 * Method to get the first node in a inventory.
 * 
 * @param  Pointer to inventory to get first node from.
 * @return Node of first item in inventory.
 */
static inline InventoryIterator inventory_first(const Inventory *inventory) {
    return inventory->first;
}

/**
 * Method to get the last node in a inventory.
 * 
 * @param  Pointer to inventory to get last node from.
 * @return Node of last item in inventory.
 */
static inline InventoryIterator inventory_last(const Inventory *inventory) {
    return inventory->last;
}

/**
 * Method to get the next node.
 * 
 * @param  Current value of iterator.
 * @return Next node in inventory.
 */
static inline InventoryIterator inventory_iteratorNext
    (const InventoryIterator i) {
    return i->next;
}

/**
 * Method to get the current stock item of the iterator.
 * 
 * @param  Iterator to be checked.
 * @return Current stock item of iterator.
 */
static inline InventoryIterator inventory_iteratorGetStockItem
    (const InventoryIterator i) {
    return i->item;
}

/**
 * Method to set and update the current stock item of a iterator.
 * 
 * @param  Iterator to be changed.
 */
static inline InventoryIterator inventory_iteratorSetStockItem
    (InventoryIterator i, const StockItem *item) {
    i->item = item;
}

/**
 * Method to allocate memory for a new inventory of stock items. Or 
 * generates error message if memory allocation fails and terminates program.
 * 
 * @return Pointer to newly created inventory.
 */
Inventory* inventory_new();

/**
 * Method to append a new stock item to the tail of a inventory. 
 * Or generates error message if memory allocation fails and terminates 
 * program.
 * 
 * @param Pointer to inventory of which will be appended to.
 * @param Pointer to Stock Item that will be appended to inventory.
 */
void inventory_add(Inventory* inventory, StockItem *item);

/**
 * Method to append a new stock item to the head of a inventory. 
 * Or generates error message if memory allocation fails and terminates 
 * program.
 * 
 * @param Pointer to inventory of which will be appended to.
 * @param Pointer to Stock Item that will be appended to inventory.
 */
void inventory_insert(Inventory* inventory, StockItem *item);

/**
 * Method to return the number of stock items currently stored in a inventory.
 * 
 * @param  Pointer to the inventory of which will be checked.
 * @return Integer value of number of elements within inventory.
 */
int inventory_count(const Inventory* inventory);

/**
 * Method to remove the stock item at the tail of a inventory
 * and return the pointer to its stock item removed.
 * 
 * @param  Pointer to the inventory where the tail will be removed.
 * @return Pointer to the Stock Item removed.
 */
StockItem *inventory_removeTail(Inventory* inventory);

/**
 * Method to remove the stock item at the head of a inventory
 * and return the pointer to its stock item removed.
 * 
 * @param  Pointer to the inventory where the head will be removed.
 * @return Pointer to the Stock Item removed.
 */
StockItem *inventory_removeHead(Inventory* inventory);

/**
 * Method to find and return a specific stock item by ID within
 * a inventory list.
 * 
 * @param  Pointer to inventory to be scanned.
 * @param  Char ID of stock item to find.
 * @return Stock Item with the ID of the parameter passed in.
 */
StockItem *inventory_find(const Inventory* inventory, const char *ID);

/**
 * Method to sort inventory by ascending order on each stock items price,
 * using the bubble sort algorithm.
 * 
 * @param Inventory pointer to inventory to be sorted.
 */
void inventory_sort(Inventory* inventory);

/**
 * Method to clear all the elements within a inventory structure.
 *  
 * @param Pointer to inventory to be cleared.
 */
void inventory_clear(Inventory* inventory);

/**
 * Method to print all elements within a inventory to the console.
 * 
 * @param Pointer to inventory to be printed.
 */
void inventory_print(const Inventory* inventory);

/**
 * Method to free inventory from memory.
 * 
 * @param Pointer to inventory to which will be freed from memory.
 */
void inventory_free(Inventory* inventory);

#ifdef __cplusplus
}
#endif

#endif /* INVENTORY_H */

