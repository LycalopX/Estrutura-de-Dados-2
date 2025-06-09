#ifndef __MAIN_FUNCTIONS_H__
#define __MAIN_FUNCTIONS_H__

#include "list.h"

// List
/**
 * @brief Creates a new list from a word.
 * 
 * @param word The word to convert into a list.
 * @return A pointer to the newly created list, or NULL if the word is invalid.
 */
List *List_FromWord(char *word);

/**
 * @brief Converts all characters in the list to uppercase.
 * 
 * @param list The list containing characters to convert.
 * @return The modified list with all characters in uppercase.
 */
List *List_WordToUpperCase(List *list);

/**
 * @brief Compares two lists for equality.
 * 
 * @param list1 The first list to compare.
 * @param list2 The second list to compare.
 * @return 1 if the lists are equal, 0 if they are not, or -1 if either list is NULL.
 */
int List_Compare(List *list1, List *list2);

/**
 * @brief Prints the elements of the list.
 * 
 * @param list The list to print.
 */
void MyPrintList(List *list);

// Char
/**
 * @brief Converts a character to uppercase.
 * 
 * @param c The character to convert.
 * @return The uppercase version of the character, or the original character if it is not lowercase.
 */
char Char_ToUpperCase(char c);

// Methods
/**
 * @brief Inserts an element into the list using binary insertion.
 * 
 * @param list The list to insert the element into.
 * @param element The element to insert.
 */
void InsertMethod_BinaryInsertion(List *list, Element *element);

/**
 * @brief Inserts an element into the list using insertion sort.
 * 
 * @param list The list to insert the element into.
 * @param element The element to insert.
 */
List *OrderMethod_InsertionUsingList(List *list);

#endif