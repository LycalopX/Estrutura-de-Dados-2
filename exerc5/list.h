#ifndef __LIST_H__
#define __LIST_H__

#include "element.h"

typedef struct{
    Element *proxy;
    unsigned int size;
} List;

/**
 * @brief Creates a new List
 * 
 * @return A pointer to the newly created List
 */
List *List_New();

/**
 * @brief Destroys a List and all its elements
 * 
 * @param list The List to be destroyed
 */
void List_Destroy(List *list);

/**
 * @brief Destroys a List without destroying its elements
 * 
 * @param list The List to be destroyed
 */
void List_DestroyWithoutElements(List *list);

/**
 * @brief Destroys a List without destroying its elements' data
 * 
 * @param list The List to be destroyed
 */
void List_DestroyWithoutElementsData(List *list);

/**
 * @brief Destroys a List without destroying its elements' data values
 * 
 * @param list The List to be destroyed
 */
void List_DestroyWithoutElementsDataValue(List *list);

// Manage Elements
/**
 * @brief Swaps two elements in the List at specified indices
 * 
 * @param list The List containing the elements to be swapped
 * @param index1 The index of the first element to swap
 * @param index2 The index of the second element to swap
 */
void List_SwapElements(List *list, unsigned int index1, unsigned int index2);

/**
 * @brief Appends an Element to the end of the List
 * 
 * @param list The List to append to
 * @param element The Element to be appended
 */
void List_Append(List *list, Element *element);

/**
 * @brief Pushes an Element to the front of the List
 * 
 * @param list The List to push to
 * @param element The Element to be pushed
 */
void List_Push(List *list, Element *element);

/**
 * @brief Inserts an Element at a specific index in the List
 * 
 * @param list The List to insert into
 * @param element The Element to be inserted
 * @param index The index at which to insert the Element
 */
void List_Insert(List *list, Element *element, unsigned int index);

/**
 * @brief Removes an Element at a specific index from the List
 * 
 * @param list The List to remove from
 * @param index The index of the Element to be removed
 */
void List_RemoveAt(List *list, unsigned int index);

// Gets
/**
 * @brief Gets the size of the List
 * 
 * @param list The List to get the size of
 * @return The size of the List
 */
unsigned int List_Size(List *list);

/**
 * @brief Counts the size of the List
 * 
 * @param self The List to count the size of
 * @return The size of the List
 */
unsigned int List_CountSize(void *self);

/**
 * @brief Gets the first Element of the List
 * 
 * @param list The List to get the first Element from
 * @return A pointer to the first Element of the List
 */
Element *List_GetFirstElement(List *list);

/**
 * @brief Gets the last Element of the List
 * 
 * @param list The List to get the last Element from
 * @return A pointer to the last Element of the List
 */
Element *List_GetLastElement(List *list);

/**
 * @brief Gets the Element at a specific index in the List
 * 
 * @param list The List to get the Element from
 * @param index The index of the Element to be retrieved
 * @return A pointer to the Element at the specified index, or NULL if the index is out of bounds
 */
Element *List_GetElementOfIndex(List *list, unsigned int index);

// Print
/**
 * @brief Prints the List and its elements
 * 
 * @param list The List to be printed
 */
void List_Print(List *list);

// GENERIC
/**
 * @brief Initializes the List type and its actions
 */
void List_InitializeType();

/**
 * @brief Gets the List data from an Element
 * 
 * @param element The Element to get the List data from
 * @return A pointer to the List data of the Element
 */
List *Element_GetListData(Element *element);

/**
 * @brief Gets the List from a Data structure
 * 
 * @param data The Data structure to get the List from
 * @return A pointer to the List contained in the Data structure
 */
List *Data_GetList(Data *data);
#endif