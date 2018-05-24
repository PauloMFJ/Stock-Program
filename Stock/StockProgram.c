/* 
 * File:   StockProgram.c
 * Author: Paulo Jorge
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "StockItem.h"
#include "Inventory.h"
#include "Date.h"
#include "Sales.h"

// Buffer size for each line in file. Although the longest line is 41
// it is bigger incase line is longer.
const int LONGEST_LINE_BUFFER = 64;
// Buffer size for words, again larger than largest word currently in file,
// for future files.
const int STRING_BUFFER = 32;
// Buffer size for date (Date length (10) + null terminator (1))
const int DATE_BUFFER = 11;

/**
 * Method to test all methods from header files to ensure that everything is 
 * fully functioning as intended before implementing working solution.
 */
void testing() {
    // ------ STOCK ITEM ------
    StockItem *item = stockItem_new("Capacitor", "CAP_300uF", 
            585, 85, "300uF");
    StockItem *item2 = stockItem_new("Diode", "1N4004", 
            194, 6, NULL);
    //stockItem_print(item);
    //printf("\n%s \n%s \n%d \n%f \n%s\n",
    //        stockItem_getType(item2), stockItem_getID(item2), 
    //        stockItem_getQuantity(item2), stockItem_getPrice(item2), 
    //        stockItem_getDesc(item2));
    //stockItem_Sell(item, 10);
    //stockItem_print(item);
    //stockItem_free(item);
    //stockItem_free(item2);
    
    // ------ DATE ------
    Date *date = date_new(1, 12, 1990);
    Date *date2 = date_new(1, 3, 1990);
    //printf("%d", date_compare(date, date2));
    //date_print(date);
    //printf("%02d/%02d/%04d\n", date_getDay(date), date_getMonth(date), 
    //        date_getYear(date));
    //printf("%s\n", date_getDate(date));
    //date_free(date);
    
    // ------ INVENTORY ------
    Inventory* inventory = inventory_new();
    inventory_add(inventory, item);
    inventory_insert(inventory, item2);
    inventory_add(inventory, item2);
    //inventory_print(inventory);
    //printf("\nInventory Count: %d.\n", inventory_count(inventory));
    
    //for (InventoryIterator i = inventory_first(inventory); i != NULL; 
    //        i = inventory_iteratorNext(i)) {
    //    stockItem_print(inventory_iteratorGetStockItem(i));
    //    
    //    inventory_iteratorSetStockItem(i, item);
    //}
    //stockItem_print(inventory_last(inventory)->item);
    //inventory_print(inventory);
    
    //StockItem *item3 = inventory_find(inventory, "CAP_300uF");
    //stockItem_print(item3);
    
    //inventory_removeTail(inventory);
    //inventory_print(inventory);
    //printf("\nInventory Count: %d.\n", inventory_count(inventory));
    
    //inventory_removeHead(inventory);
    //inventory_print(inventory);
    //printf("\nInventory Count: %d.\n", inventory_count(inventory));
        
    // ------ SALES ------
    Sales* sales = sales_new();
    sales_add(sales, inventory, date, 
            "CAP_300uF", 10);
    sales_insert(sales, inventory, date, 
            "1N4004", 5);
    sales_add(sales, inventory, date, 
            "CAP_300uF", 2);
    //sales_print(sales);
    //printf("\nSales Count: %d.\n", sales_count(sales));
    
    //for (SalesIterator i = sales_first(sales); i != NULL; 
    //        i = sales_iteratorNext(i)) {
    //    sales_printSale(sales_iteratorGetCurrent(i));
    //}
    //sales_printSale(sales_last(sales));
    
    //sales_removeTail(sales);
    //sales_print(sales);
    //printf("\nSales Count: %d.\n", sales_count(sales));
    
    //sales_removeHead(sales);
    //sales_print(sales);
    //printf("\nSales Count: %d.\n", sales_count(sales));
    
    inventory_free(inventory);
    sales_free(sales);    
}

/**
 * Method to read stock items from a file and add each one into a 
 * existing inventory.
 * 
 * @param Pointer to inventory where all stock items will be added to.
 * @param File name of file to be read. 
 */
void read_inventory(Inventory* inventory, const char *fileName) {    
    // Open file in read mode
    FILE *file = fopen(fileName, "r");
    
    // Null check if file has correctly opened
    if(!file) {
        fprintf(stderr, "Error: Unable to open '%s' in mode 'r' "
                "in read_inventory().\n", fileName);
        exit(EXIT_FAILURE);
    }
    
    // Initialise local line variable
    char line[LONGEST_LINE_BUFFER];

    // Loop each line in file
    while (fgets(line, LONGEST_LINE_BUFFER, file)) { 
        // Initialise stock item variables to global heap
        char *type = (char*)malloc(sizeof(char) * STRING_BUFFER);
        char *ID = (char*)malloc(sizeof(char) * STRING_BUFFER);
        char *quantity = (char*)malloc(sizeof(char) * STRING_BUFFER);
        char *price = (char*)malloc(sizeof(char) * STRING_BUFFER);
        char *desc = (char*)malloc(sizeof(char) * STRING_BUFFER);

        // Read line into variables
        sscanf(line, "%[^, \t\n], %[^, \t\n], %[^, \t\n], %[^, \t\n], "
                "%s", 
                type, ID, quantity, price, desc);
        
        // As diode doesn't have a description, assign it as N/A
        if (strcmp(type, "diode") == 0)
            strncpy(desc, "N/A", sizeof(desc));
               
        // Create new stock item
        StockItem *item = stockItem_new(type, ID, atoi(quantity), 
                atoi(price), desc);

        // Add stock item to inventory
        inventory_add(inventory, item);
    }
    
    // Close File
    fclose(file);
}

/**
 * Method to read sales from a file and add each one into a 
 * existing sales list.
 * 
 * @param Pointer to sales list where all sales will be added to.
 * @param File name of file to be read. 
 */
void read_sales(Sales* sales, Inventory* inventory, const char *fileName) {    
    // Open file in read mode
    FILE *file = fopen(fileName, "r");
    
    // Null check if file has correctly opened
    if(!file) {
        fprintf(stderr, "Error: Unable to open '%s' in mode 'r' "
                "in read_sales().\n", fileName);
        exit(EXIT_FAILURE);
    }
    
    // Initialise local line variable
    char line[LONGEST_LINE_BUFFER];

    // Loop each line in file
    while (fgets(line, LONGEST_LINE_BUFFER, file)) {       
        // Initialise sales variables to global heap
        char *day = (char*)malloc(sizeof(char) * STRING_BUFFER);
        char *month = (char*)malloc(sizeof(char) * STRING_BUFFER);
        char *year = (char*)malloc(sizeof(char) * STRING_BUFFER);
        char *ID = (char*)malloc(sizeof(char) * STRING_BUFFER);
        char *quantity = (char*)malloc(sizeof(char) * STRING_BUFFER);

        // Read line into variables
        sscanf(line, "%[^/]/%[^/]/%[^, \t\n], %[^,\t\n], %[^ \t\n]"
                "%[^ \t\n]", 
                day, month, year, ID, quantity);
        
        // Allocate date to memory
        Date *date = date_new(atoi(day), atoi(month), atoi(year));
        
        // Add this sale to sales list
        sales_add(sales, inventory, date, ID, atoi(quantity));
    }
    
    // Close File
    fclose(file);
}

/**
 * Method to calculate and return the date with the highest sales total.
 * 
 * @param  Sales list to get sales information from.
 * @return Date string with the highest sales total.
 */
char *highestSalesDate(Sales* sales) {
    // Date string of current day and date with highest sales
    char *currentDate = (char*)malloc(sizeof(char) * DATE_BUFFER);
    char *dateHighest = (char*)malloc(sizeof(char) * DATE_BUFFER);
            
    // Current used to store sales within the current date
    float current = 0;
    // Highest date sales value based on current
    float highest = 0;

    // Loop all sales nodes
    for (SalesNode* node = sales->first; node != NULL; 
            node = node->next) {
        // If date changes
        if (strcmp(currentDate, date_getDate(node->date)) != 0) {
            // Set current date as the return date if it had the highest sales
            if (current > highest) {
                highest = current;
                strncpy(dateHighest, currentDate, DATE_BUFFER);
            }
            
            // Reset values for the next cycle
            strncpy(currentDate, date_getDate(node->date), DATE_BUFFER);
            current = 0;
        }
        
        // Increase the current total for this date
        current += sales_getCost(node);
    }
    
    return dateHighest;
}

int NPNTransistorsCount(Inventory* inventory) {
    int count = 0;
    // If inventory is not empty
    if (inventory->first != NULL) {
        // Loop all nodes within inventory
        for(InventoryNode* node = inventory->first; node != NULL;
                node = node->next) {
            // Get item from node
            StockItem *item = node->item;
                        
            // If current node is a transistor and has NPN as description add
            // its quantity to total count
            if ((strcmp("transistor", stockItem_getType(item)) == 0) 
                    && (strcmp("NPN", stockItem_getDesc(item)) == 0)) 
                count += stockItem_getQuantity(item);
        }
    // Else display error message to console
    } else
        fprintf(stderr, "Error: Inventory empty in "
                "NPNTransistorsCount().\n");
    
    return count;
}

char *resistanceOfRegisters(Inventory* inventory) {    
    // Used to output the resistance in the form of BS 1852 letter coding
    char *resistance = (char*)malloc(sizeof(char) * STRING_BUFFER);
    
    // Total resistance of registers
    double totalResistance = 0;
    
    // If inventory is not empty
    if (inventory->first != NULL) {
        // Loop all nodes within inventory
        for(InventoryNode* node = inventory->first; node != NULL;
                node = node->next) {
            // Get item from node
            StockItem *item = node->item;
            
            // If this stock item is a resistor and has stock
            if ((strcmp("resistor", stockItem_getType(item)) == 0
                    && (stockItem_getQuantity(item) > 0))) {
                
                // Get pointer to description
                char *desc = stockItem_getDesc(item);
                // Used as boolean state
                int side = 1;
                // Type of resistance and strength
                char type;
                // Long instead of integer to support larger resistances
                long integer = 0;
                long decimal = 0;
                
                for (int i = 0; i < strlen(desc); i++) {
                    // Get type of resistance
                    if(isalpha(desc[i])) {
                        type = desc[i];
                        // Change current side
                        side = 0;
                    } 
                    else if (side) 
                        // Get left side integer of type symbol
                        integer = integer * 10 + (desc[i] - 48);
                    else
                        // Get right side integer of ohm symbol
                        decimal = decimal * 10 + (desc[i] - 48);
                }
   
                // Add integer part of resistance to decimal part
                integer = (integer + (decimal / 10));

                // Determine type and multiple value by its amount
                if(type == 'K')
                    integer = integer * 1000;
                else if (type == 'M')
                    integer = integer * 1000000;
                
                // Increase total by this resistors resistance * quantity
                totalResistance += (integer * stockItem_getQuantity(item));
            }
        }
    // Else display error message to console
    } else
        fprintf(stderr, "Error: Inventory empty in "
                "resistanceOfRegisters().\n");
    
    // Determine type of resistance and divide by given type
    char type;
    if ((totalResistance / 1000) < 1)
        type = 'R';
    else if ((totalResistance / 1000000) < 1) {
        type = 'K';
        totalResistance = totalResistance / 1000;
    }
    else {
        type = 'M';
        totalResistance = totalResistance / 1000000;
    }
    
    // Get decimal part of total resistance
    int decimal = (long)((totalResistance - (long)totalResistance) * 10);
    
    // Format output string and return
    snprintf(resistance, STRING_BUFFER, "%d%c%d", 
             (int)totalResistance, type, decimal);
    return resistance;
}

/**
 * Main used to run program outputs.
 * 
 * @return Exit success integer. 
 */
int main(int argc, char** argv) {
    printf(" --- Stock Program --- \n");
      
    // Run testing data performed on program
    //testing();
    
    // Initialise new inventory list
    Inventory* inventory = inventory_new();
    // Read inventory file into the inventory
    read_inventory(inventory, "inventory.txt");

    // Initialise new sales list
    Sales* sales = sales_new();
    // Read sales file into the sales list
    read_sales(sales, inventory, "sales.txt");
    
    // ------------ Query 1: ------------
    printf("\nQUERY 1: Inventory (Sorted on increasing price):");
    // Sort inventory
    inventory_sort(inventory);
    // Print file to output
    inventory_print(inventory);
    
    // Print inventory count to output
    printf("\nInventory Count: %d.\n", inventory_count(inventory));

    // ------------ Query 2: ------------
    printf("\nQUERY 2: Date with the greatest sales volume (Based on the day "
            "with the highest sales total):\n");
    // Print date with highest sales to output
    printf("%s yielded highest sales volume.\n", highestSalesDate(sales));
    
    // ------------ Query 3: ------------
    printf("\nQUERY 3: Total NPN transistors in stock after processing sales:"
            "\n");
    // Print number of transistors in stock
    printf("%d in stock.\n", NPNTransistorsCount(inventory));

    // ------------ Query 4: ------------
    printf("\nQUERY 4: Total resistance of all remaining registers in stock:"
            "\n");
    printf("%s\u2126 total resistance.\n", resistanceOfRegisters(inventory));
    
    // Free all from memory
    inventory_free(inventory);
    sales_free(sales);
    
    return EXIT_SUCCESS;
}
