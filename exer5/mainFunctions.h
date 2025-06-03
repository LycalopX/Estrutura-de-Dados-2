#ifndef __MAIN_FUNCTIONS_H__
#define __MAIN_FUNCTIONS_H__

#include "list.h"

// List
List *List_FromWord(char *word);
List *List_WordToUpperCase(List *list);
int List_Compare(List *list1, List *list2);
void MyPrintList(List *list);

// Char
char Char_ToUpperCase(char c);

// Methods
void InsertMethod_BinaryInsertion(List *list, Element *element);
List *OrderMethod_InsertionUsingList(List *list);

#endif