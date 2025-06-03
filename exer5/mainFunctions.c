#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mainFunctions.h"

/*
    LIST FUNCTIONS
*/

List *List_FromWord(char *word)
{
    // Validate the input word
    if (word == NULL || *word == '\0')
    {
        return NULL;
    }

    List *list = List_New();
    while (*word != '\0')
    {
        char *value = malloc(sizeof(char));
        value[0] = *word;
        Element *element = Element_New("char", value);
        List_Append(list, element);
        word++;
    }
    return list;
}

List *List_WordToUpperCase(List *list)
{
    if (list == NULL)
    {
        return NULL;
    }

    for (unsigned int i = 0; i < List_Size(list); i++)
    {
        Element *element = List_GetElementOfIndex(list, i);
        if (element != NULL)
        {
            char *value = Element_GetDataValue(element);
            *value = Char_ToUpperCase(*value);
        }
    }

    return list;
}

int List_Compare(List *list1, List *list2)
{
    // Same list
    if (list1 == list2)
    {
        return 1;
    }

    // Validate the input lists
    if (list1 == NULL || list2 == NULL)
    {
        return -1;
    }

    for (unsigned int i = 0; i < List_Size(list1); i++)
    {
        Element *element1 = List_GetElementOfIndex(list1, i);
        Element *element2 = List_GetElementOfIndex(list2, i);
        if (Data_Compare(Element_GetData(element1), Element_GetData(element2)) != 0)
        {
            return 0; // Elements are not equal
        }
    }

    return 1; // Lists are equal
}

void MyPrintList(List *list)
{
    if (list == NULL)
    {
        printf("List is NULL\n");
        return;
    }

    Element *element = List_GetFirstElement(list);
    while (element != NULL)
    {
        Element_Print(element);
        element = Element_Next(element);
    }
}

/*
    CHAR FUNCTIONS
*/

char Char_ToUpperCase(char c)
{
    // Validation
    if (c >= 'a' && c <= 'z')
    {
        return c - ('a' - 'A');
    }
    return c;
}

/*
    METHODS
*/

void InsertMethod_BinaryInsertion(List *list, Element *element)
{
    if (list == NULL || element == NULL)
    {
        return;
    }

    int low = 0;
    int high = List_Size(list) - 1;
    int mid;
    while (low <= high)
    {
        mid = (low + high) / 2;
        int cmp = Data_Compare(Element_GetData(element), Element_GetData(List_GetElementOfIndex(list, mid)));

        if (cmp < 0)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    List_Insert(list, element, low);
}

List *OrderMethod_InsertionUsingList(List *list)
{
    List *sortedList = List_New();
    List_Push(sortedList, Element_Copy(List_GetFirstElement(list)));

    for (unsigned i = 1; i < List_Size(list); i++)
    {
        Element *currentElement = List_GetElementOfIndex(list, i);
        Element *insertElement = Element_Copy(currentElement);
        InsertMethod_BinaryInsertion(sortedList, insertElement);
    }

    return sortedList;
}