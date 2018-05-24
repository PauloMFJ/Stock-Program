/* 
 * File:   Sales.c
 * Author: Paulo Jorge
 */

#include <stdio.h>
#include <stdlib.h>

#include "Date.h"

// Buffer size for date (Date length (10) + null terminator (1))
const int SALES_DATE_BUFFER = 11;

/**
 * Method to allocate memory for a new date containing information 
 * about itself. Or generates error message if memory allocation fails
 * and terminates program.
 * 
 * @param  Day integer, such as 9.
 * @param  Month integer, such as 10.
 * @param  Full year integer value, such as 2017.
 * @return Pointer to newly created date type.
 */
Date* date_new(int day, int month, int year) {
    // Allocate date to memory
    Date *date = (Date*)malloc(sizeof(Date));
    // Null check memory allocation
    if (!date) {
        fprintf(stderr, "Error: Unable to allocate memory in "
                "date_new().\n");
        exit(EXIT_FAILURE);
    }
    
    // Ensure that date is valid
    if ((day > 0) && (day <= 31) 
            && (month > 0) && (month <= 12)  
            && (year >= 1000) && (year <= 9999)) {
        date->day   = day;
        date->month = month;
        date->year  = year;
    // Else output error and exit program
    } else {
        fprintf(stderr, "Error: Date provided is not valid "
                "in date_new().\n");
        exit(EXIT_FAILURE);
    }
    return date;
}

/**
 * Method to compare two dates and return the result of which one is newer. 
 * 
 * @param  Pointer to date to compare against.
 * @param  Pointer to second date to compare against the first date.
 * @return Returns 0 if date 1 is newer than date 2 or 1 if older.
 */
int date_compare(const Date* date1, const Date* date2) {
    // Compare dates
    if (date_getYear(date1) > date_getYear(date2))
        return 0;
    else if (date_getMonth(date1) > date_getMonth(date2))
        return 0;
    else if (date_getDay(date1) > date_getDay(date2))
        return 0;
    return 1;
}

/**
 * Method used to get the day from a date.
 * 
 * @param  Pointer to date used to return.
 * @return Day integer.
 */
int date_getDay(const Date *date) {
    return date->day;
}

/**
 * Method used to get the month from a date.
 * 
 * @param  Pointer to date used to return.
 * @return Month integer.
 */
int date_getMonth(const Date *date) { 
    return date->month;
}

/**
 * Method used to get the year from a date.
 * 
 * @param  Pointer to date used to return.
 * @return Year integer.
 */
int date_getYear(const Date *date) {
    return date->year;
}

/**
 * Get method to get formatted date string of a date.
 * 
 * @param  Pointer to date used to return.
 * @return Formatted date string. 
 */
char *date_getDate(const Date *date) {
     // Convert date variables into char
    char *formattedDate = (char*)malloc(sizeof(char) * SALES_DATE_BUFFER);
    snprintf(formattedDate, SALES_DATE_BUFFER, "%02d/%02d/%04d", 
             date->day, date->month, date->year);

    return formattedDate;
}

/**
 * Method to print out a date.
 * 
 * @param  Pointer to date to be printed.
 * @return Print of date information.
 */
void date_print(const Date *date) {
        printf("\nDate: %s\n", date_getDate(date));
}

/**
 * Method to free a date from memory.
 * 
 * @param Pointer to date to which will be freed from memory.
 */
void date_free(Date *date) {
    free(date);
}