#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mainFunctions.h"

/*
    LIST FUNCTIONS
*/

// Converts a string into a list of character elements
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
        char *value = malloc(sizeof(char)); // Allocate memory for a single character
        value[0] = *word;
        Element *element = Element_New("char", value);
        List_Append(list, element); // Append each character as an element to the list
        word++;
    }
    return list;
}

// Converts all characters in the list to uppercase
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
            *value = Char_ToUpperCase(*value); // Convert char to uppercase
        }
    }

    return list;
}

// Compares two lists element by element
int List_Compare(List *list1, List *list2)
{
    // Check if they are the same reference
    if (list1 == list2)
    {
        return 1;
    }

    // Null check
    if (list1 == NULL || list2 == NULL)
    {
        return -1;
    }

    // Compare each element using Data_Compare
    for (unsigned int i = 0; i < List_Size(list1); i++)
    {
        Element *element1 = List_GetElementOfIndex(list1, i);
        Element *element2 = List_GetElementOfIndex(list2, i);
        if (Data_Compare(Element_GetData(element1), Element_GetData(element2)) != 0)
        {
            return 0; // Found a mismatch
        }
    }

    return 1; // All elements matched
}

// Prints the list elements using Element_Print
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
        element = Element_Next(element); // Move to next element
    }
}

/*
    CHAR FUNCTIONS
*/

// Converts a lowercase letter to uppercase, returns unchanged otherwise
char Char_ToUpperCase(char c)
{
    if (c >= 'a' && c <= 'z')
    {
        return c - ('a' - 'A');
    }
    return c;
}

/*
    METHODS
*/

// Inserts an element into a sorted list using binary search to find the correct position
void InsertMethod_BinaryInsertion(List *list, Element *element)
{
    if (list == NULL || element == NULL)
    {
        return;
    }

    int low = 0;
    int high = List_Size(list) - 1;
    int mid;

    // Binary search loop to find the correct insert position
    while (low <= high)
    {
        mid = (low + high) / 2;
        int cmp = Data_Compare(
            Element_GetData(element),
            Element_GetData(List_GetElementOfIndex(list, mid))
        );

        if (cmp < 0)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    // Insert element at the found position
    List_Insert(list, element, low);
}

// Creates a new sorted list using binary insertion sort on a copy of the original list
List *OrderMethod_InsertionUsingList(List *list)
{
    List *sortedList = List_New();

    // Push the first element directly
    List_Push(sortedList, Element_Copy(List_GetFirstElement(list)));

    // Iterate over the remaining elements and insert them into the sorted list
    for (unsigned i = 1; i < List_Size(list); i++)
    {
        Element *currentElement = List_GetElementOfIndex(list, i);
        Element *insertElement = Element_Copy(currentElement);
        InsertMethod_BinaryInsertion(sortedList, insertElement);
    }

    return sortedList;
}
