/* 
 * File:   Sales.c
 * Author: Paulo Jorge.
 */

#include <stdio.h>
#include <stdlib.h>

#include "StockItem.h"
#include "Inventory.h"
#include "Sales.h"

/**
 * Method to allocate memory for a new sales list of sales. Or 
 * generates error message if memory allocation fails and terminates program.
 * 
 * @return Pointer to newly created sales.
 */
Sales* sales_new() {
    // Allocate sales to memory
    Sales* sales = (Sales*)malloc(sizeof(Sales));
    // Null check memory allocation
    if (!sales) {
        fprintf(stderr, "Error: Unable to allocate memory in "
                "sales_new().\n");
        exit(EXIT_FAILURE);
    }

    // As empty, default first and last to null
    sales->first = NULL;
    sales->last  = NULL;
    
    return sales;
}

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
        int quantity) {
    // Allocate node to memory
    SalesNode* node = (SalesNode*)malloc(sizeof(SalesNode));
    // Null check memory allocation
    if (!node) {
        fprintf(stderr, "Error: Unable to allocate memory "
                "in sales_add().\n");
        exit(EXIT_FAILURE);
    }
    
    // Find item sold
    StockItem *item = inventory_find(inventory, ID);
    
    // Only allow sale if stock item exists and stock item has sufficient stock
    if(item && (stockItem_Sell(item, quantity) == 1)) {
        // Pass in sales information
        node->item     = item;
        node->date     = date;
        node->ID       = ID;
        node->quantity = quantity;
        node->next     = NULL;

        // If sales list is empty, set this as first and last
        if (sales->last == NULL)
            sales->first = sales->last = node;
        // Else add this to tail of inventory
        else
            sales->last = sales->last->next = node;
    }
    // Else free node from memory as it was unassigned
    else
        sales_free(node);
}

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
        int quantity) {
    // Allocate node to memory
    SalesNode* node = (SalesNode*)malloc(sizeof(SalesNode));
    // Null check memory allocation
    if (!node) {
        fprintf(stderr, "Error: Unable to allocate memory "
                "in sales_insert().\n");
        exit(EXIT_FAILURE);
    }
    
    // Find item sold
    StockItem *item = inventory_find(inventory, ID);
    
    // Only allow sale if stock item exists and stock item has sufficient stock
    if(item && (stockItem_Sell(item, quantity) == 1)) {
        // Pass in sales information
        node->item     = item;
        node->date     = date;
        node->ID       = ID;
        node->quantity = quantity;
        node->next     = sales->first;

        // If sales list is empty, set this as first and last
        if (sales->last == NULL)
            sales->first = sales->last = node;
        // Else add to head of the sales list
        else
            sales->first = node;
    }
    // Else free node from memory as it was unassigned
    else
        sales_free(node);
}

/**
 * Method to return the number of sales currently stored in a sales list.
 * 
 * @param  Pointer to the sales list of which will be checked.
 * @return Integer value of number of elements within sales.
 */
int sales_count(const Sales* sales) {
    int count = 0;
    // Count number of nodes in inventory
    for (SalesNode* node = sales->first; node != NULL; 
            node = node->next)
        count++;
    
    return count;
}

/**
 * Method to remove a sale at the tail of a sales list.
 * 
 * @param  Pointer to the sales list where the tail will be removed.
 */
void sales_removeTail(Sales* sales)  {
    // Null check if sales list is empty
    if (sales->first == NULL) {
        fprintf(stderr, "Error: Attempting to remove the tail from an empty "
                "sales list in sales_removeTail().\n");
        exit(EXIT_FAILURE);
    }
    
    // Get tail of sales list
    SalesNode* tail = sales->last;
    
    // If sales only has one item, set first and last to null
    if (sales->first == sales->last)
        sales->first = sales->last = NULL;
    else {
        SalesNode* node;
        // Find the second to last node
        for (node = sales->first; node->next != tail; node = node->next);
 
        // Set this node as last
        sales->last       = node;
        // Remove previously last node
        sales->last->next = NULL;
    }
    
    // Free tail from memory
    free(tail);
}

/**
 * Method to remove the a sale at the head of a sales list.
 * 
 * @param  Pointer to the sales list where the head will be removed.
 */
void sales_removeHead(Sales* sales) {
        // Null check if sales is empty
    if (sales->first == NULL) {
        fprintf(stderr, "Error: Attempting to remove the head from an empty "
                "inventory in sales_removeHead().\n");
        exit(EXIT_FAILURE);
    }
    
    // Get head of sales list
    SalesNode* head = sales->first;
    
    // If sales only has one node, set first and last to null
    if (sales->first == sales->last)
        sales->first = sales->last = NULL;
    // Else set previously second node to first
    else
        sales->first = sales->first->next;  
        
    // Free head from memory
    free(head);
}

/**
 * Method to clear all the elements within a sales list structure.
 *  
 * @param Pointer to sales list to be cleared.
 */
void sales_clear(Sales* sales) { 
    // While sales is not empty remove from head to tail each
    // node one by one
    while (sales->first != NULL) {
        SalesNode* node = sales->first;
        sales->first = node->next;
        
        // Free node from memory
        free(node);
    }
}

/**
 * Get method to get ID of a sales node.
 * 
 * @param  Pointer to sales node containing ID.
 * @return ID char. 
 */
char *sales_getID(const SalesNode* node) {
    return node->ID;
}

/**
 * Get method to get quantity of a sales node.
 * 
 * @param  Pointer to sales node containing quantity.
 * @return Integer quantity value. 
 */
int sales_getQuantity(const SalesNode* node) {
    return node->quantity;
}

/**
 * Get method to get total cost of a sales node.
 * 
 * @param  Pointer to sales node containing quantity and
 *         reference to stock item sold.
 * @return Float total cost value in pounds. 
 */
float sales_getCost(const SalesNode* node) {
    return stockItem_getPrice(node->item) * (float)node->quantity;
}

/**
 * Method to print a specific sales node to the console.
 * 
 * @param Pointer to sales node to be printed.
 */
void sales_printSale(const SalesNode *node) {
    // Print sale information
    printf("\nDate:           %s\n"
             "ID:             %s\n"
             "Quantity:       %d\n"
             "Price per item: £%.2f\n"
             "Cost of Sale:   £%.2f\n",
             date_getDate(node->date), 
             sales_getID(node), 
             sales_getQuantity(node), 
             stockItem_getPrice(node->item),
             sales_getCost(node));
}

/**
 * Method to print all elements within a sales list to the console.
 * 
 * @param Pointer to sales list to be printed.
 */
void sales_print(const Sales* sales)  {
    // Loop and print all nodes if sales list is not empty
    if (sales->first != NULL)
        for(SalesNode* node = sales->first; node != NULL; 
                node = node->next) {
            // Print sale information
            printf("\nDate:           %s\n"
                     "ID:             %s\n"
                     "Quantity:       %d\n"
                     "Price per item: £%.2f\n"
                     "Cost of Sale:   £%.2f\n",
                     date_getDate(node->date), 
                     sales_getID(node), 
                     sales_getQuantity(node), 
                     stockItem_getPrice(node->item),
                     sales_getCost(node));
        }   
    // Else display empty message to console
    else
        printf("No sale has been made.\n");
}

/**
 * Method to free sales list from memory.
 * 
 * @param Pointer to sales list to which will be freed from memory.
 */
void sales_free(Sales* sales){
    // Free all nodes from sales before freeing sales list
    sales_clear(sales);
    
    free(sales);
}