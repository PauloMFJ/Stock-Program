/* 
 * File:   Sales.c
 * Author: Paulo Jorge
 */

#ifndef DATE_H
#define DATE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Node structure defining and containing information about a date.
 */
typedef struct dateStruct {
    int day, month, year;
}
Date;

/**
 * Method to allocate memory for a new date containing information 
 * about itself. Or generates error message if memory allocation fails
 * and terminates program.
 * 
 * @param  Day integer, such as 9 without leading 0's.
 * @param  Month integer, such as 10 without leading 0's.
 * @param  Full year integer value, such as 2017.
 * @return Pointer to newly created date type.
 */
Date* date_new(int day, int month, int year);

/**
 * Method to compare two dates and return the result of which one is newer. 
 * 
 * @param  Pointer to date to compare against.
 * @param  Pointer to second date to compare against the first date.
 * @return Returns 0 if date 1 is newer than date 2 or 1 if older.
 */
int date_compare(const Date* date1, const Date* date2);

/**
 * Method used to get the day from a date.
 * 
 * @param  Pointer to date used to return.
 * @return Day integer.
 */
int date_getDay(const Date *date);

/**
 * Method used to get the month from a date.
 * 
 * @param  Pointer to date used to return.
 * @return Month integer.
 */
int date_getMonth(const Date *date);

/**
 * Method used to get the year from a date.
 * 
 * @param  Pointer to date used to return.
 * @return Year integer.
 */
int date_getYear(const Date *date);

/**
 * Get method to get formatted date string of a date.
 * 
 * @param  Pointer to date used to return.
 * @return Formatted date string. 
 */
char *date_getDate(const Date *date);

/**
 * Method to print out a date.
 * 
 * @param  Pointer to date to be printed.
 * @return Print of date information.
 */
void date_print(const Date *date);

/**
 * Method to free a date from memory.
 * 
 * @param Pointer to date to which will be freed from memory.
 */
void date_free(Date *date);

#ifdef __cplusplus
}
#endif

#endif /* DATE_H */

