/* 
 * File:   Inventory.c
 * Author: Paulo Jorge
 */

#include <stdio.h>
#include <stdlib.h>

#include "Inventory.h"
#include "StockItem.h"

/**
 * Method to allocate memory for a new inventory of stock items. Or 
 * generates error message if memory allocation fails and terminates program.
 * 
 * @return Pointer to newly created inventory.
 */
Inventory* inventory_new() {
    // Allocate inventory to memory
    Inventory* inventory = (Inventory*)malloc(sizeof(Inventory));
    // Null check memory allocation
    if (!inventory) {
        fprintf(stderr, "Error: Unable to allocate memory in "
                "inventory_new().\n");
        exit(EXIT_FAILURE);
    }

    // As empty, default first and last to null
    inventory->first = NULL;
    inventory->last  = NULL;
    
    return inventory;
}

/**
 * Method to append a new stock item to the tail of a inventory. 
 * Or generates error message if memory allocation fails and terminates 
 * program.
 * 
 * @param Pointer to inventory of which will be appended to.
 * @param Pointer to Stock Item that will be appended to inventory.
 */
void inventory_add(Inventory* inventory, StockItem *item) {
    // Allocate node to memory
    InventoryNode* node = (InventoryNode*)malloc(sizeof(InventoryNode));
    // Null check memory allocation
    if (!node) {
        fprintf(stderr, "Error: Unable to allocate memory "
                "in inventory_add().\n");
        exit(EXIT_FAILURE);
    }
    
    // Pass in stock item
    node->item = item;
    node->next = NULL;

    // If inventory is empty, set this as first and last
    if (inventory->last == NULL)
        inventory->first = inventory->last = node;
    // Else add to tail of inventory
    else
        inventory->last = inventory->last->next = node;
}

/**
 * Method to append a new stock item to the head of a inventory. 
 * Or generates error message if memory allocation fails and terminates 
 * program.
 * 
 * @param Pointer to inventory of which will be appended to.
 * @param Pointer to Stock Item that will be appended to inventory.
 */
void inventory_insert(Inventory* inventory, StockItem *item) {
    // Allocate node to memory
    InventoryNode* node = (InventoryNode*)malloc(sizeof(InventoryNode));
    // Null check memory allocation
    if (!node) {
        fprintf(stderr, "Error: Unable to allocate memory "
                "in inventory_add().\n");
        exit(EXIT_FAILURE);
    }
    
    node->item = item;
    node->next = inventory->first;
    
    // If inventory is empty, set this as first and last
    if (inventory->last == NULL)
        inventory->first = inventory->last = node;
    // Else add to head of inventory
    else
        inventory->first = node;
}

/**
 * Method to return the number of stock items currently stored in a inventory.
 * 
 * @param  Pointer to the inventory of which will be checked.
 * @return Integer value of number of elements within inventory.
 */
int inventory_count(const Inventory* inventory) {
    int count = 0;
    // Count number of nodes in inventory
    for (InventoryNode* node = inventory->first; node != NULL; 
            node = node->next)
        count++;
    
    return count;
}

/**
 * Method to remove the stock item at the tail of a inventory
 * and return the pointer to its stock item removed.
 * 
 * @param  Pointer to the inventory where the tail will be removed.
 * @return Pointer to the Stock Item removed.
 */
StockItem *inventory_removeTail(Inventory* inventory) {
    // Null check if inventory is empty
    if (inventory->first == NULL) {
        fprintf(stderr, "Error: Attempting to remove the tail from an empty "
                "inventory in inventory_removeTail().\n");
        exit(EXIT_FAILURE);
    }
    
    // Get stock item to be deleted
    StockItem *item = inventory->last->item;
    
    // Get tail of inventory
    InventoryNode* tail = inventory->last;
    
    // If inventory only has one item, set first and last to null
    if (inventory->first == inventory->last)
        inventory->first = inventory->last = NULL;
    else {
        InventoryNode* node;
        // Find the second to last node
        for (node = inventory->first; node->next != tail; node = node->next);
 
        // Set this node as last
        inventory->last       = node;
        // Remove previously last node
        inventory->last->next = NULL;
    }
    
    // Free tail from memory
    free(tail);
    
    return item;
}

/**
 * Method to remove the stock item at the head of a inventory
 * and return the pointer to its stock item removed.
 * 
 * @param  Pointer to the inventory where the head will be removed.
 * @return Pointer to the Stock Item removed.
 */
StockItem *inventory_removeHead(Inventory* inventory) { 
    // Null check if inventory is empty
    if (inventory->first == NULL) {
        fprintf(stderr, "Error: Attempting to remove the head from an empty "
                "inventory in inventory_removeHead().\n");
        exit(EXIT_FAILURE);
    }
    
    // Get stock item to be deleted
    StockItem *item = inventory->first->item;
    
    // Get head of inventory
    InventoryNode* head = inventory->first;
    
    // If inventory only has one node, set first and last to null
    if (inventory->first == inventory->last)
        inventory->first = inventory->last = NULL;
    // Else set previously second node to first
    else
        inventory->first = inventory->first->next;  
        
    // Free head from memory
    free(head);
    
    return item;
}

/**
 * Method to find and return a specific stock item by ID within
 * a inventory list.
 * 
 * @param  Pointer to inventory to be scanned.
 * @param  Char ID of stock item to find.
 * @return Stock Item with the ID of the parameter passed in.
 */
StockItem *inventory_find(const Inventory* inventory, const char *ID) {
    // Loop and compare all nodes against ID
    if (inventory->first != NULL)
        for (InventoryNode *node = inventory->first; node != NULL; 
                node = node->next) {
            // Get stock item to compare
            StockItem *item = node->item;

            // Compare this items ID against passed in ID
            if(strcmp(stockItem_getID(item), ID) == 0)
                return item;
        }   
    // Display error message if nothing was found
    fprintf(stderr, "Error: Stock item ID %s not found in"
            "inventory_find().\n", ID);
    return NULL;
}

/**
 * Method to sort inventory by order of increasing price,
 * using the bubble sort algorithm.
 * 
 * @param Inventory pointer to inventory to be sorted.
 */
void inventory_sort(Inventory* inventory) {  
    // Only sort if inventory contains at least 2 different nodes
    if (inventory->first != inventory->last)
    {
        // State of sorted
        int sorted;

        // Loop while not sorted
        do {
            sorted = 1; 

            // Loop all nodes
            for (InventoryNode* node = inventory->first; node->next != NULL; 
                    node = node->next) {
                // Get items to be sorted
                StockItem *item  = node->item;
                StockItem *nextItem  = node->next->item;
                
                // If this item is worth more than next item swap positions
                if (stockItem_getPrice(item) > stockItem_getPrice(nextItem)) {
                   node->item        = nextItem;
                   node->next->item  = item;
                   sorted            = 0;
                }
            }
        } while (!sorted);
    }
}

/**
 * Method to clear all the elements within a inventory structure.
 *  
 * @param Pointer to inventory to be cleared.
 */
void inventory_clear(Inventory* inventory) { 
    // While inventory is not empty remove from head to tail each
    // node one by one
    while (inventory->first != NULL) {
        InventoryNode* node = inventory->first;
        inventory->first = node->next;
        
        // Free node from memory
        free(node);
    }
}

/**
 * Method to print all elements within a inventory to the console.
 * 
 * @param Pointer to inventory to be printed.
 */
void inventory_print(const Inventory* inventory) {
    // Loop and print all nodes if inventory is not empty
    if (inventory->first != NULL)
        for (InventoryNode* node = inventory->first; node != NULL; 
                node = node->next) {
            // Get stock item to print
            StockItem *item = node->item;
            
            // Print item information to console
            stockItem_print(item);
        }
    // Else display empty message to console
    else
        printf("\nInventory currently empty.\n");
}

/**
 * Method to free inventory from memory.
 * 
 * @param Pointer to inventory to which will be freed from memory.
 */
void inventory_free(Inventory* inventory) {
    // Free all nodes from inventory before freeing inventory
    inventory_clear(inventory);

    free(inventory);
}
