#include <stdlib.h>
#include <stdio.h>

#include "list.h"

// Create and initialize a new List instance
List *List_New(){
    List *newList = malloc(sizeof(List));
    newList->proxy = NULL; // Head of the list
    newList->size = 0;
    return newList;
}

// Destroys the list and all its elements (including their data)
void List_Destroy(List *list){
    Element *element = List_GetFirstElement(list);
    while(element != NULL){
        list->proxy = Element_Next(element);
        Element_Destroy(element);
        element = list->proxy;
    }

    free(list);
}

// Destroys the list object only, leaves elements intact
void List_DestroyWithoutElements(List *list){
    free(list);
}

// Destroys the list and its elements, but not the data inside the elements
void List_DestroyWithoutElementsData(List *list){
    Element *element = List_GetFirstElement(list);
    while(element != NULL){
        list->proxy = Element_Next(element);
        Element_DestroyWithoutData(element);
        element = list->proxy;
    }

    free(list);
}

// Destroys the list and its elements, but not the value stored in the data (e.g., if value is reused)
void List_DestroyWithoutElementsDataValue(List *list){
    Element *element = List_GetFirstElement(list);
    while(element != NULL){
        list->proxy = Element_Next(element);
        Element_DestroyWithoutDataValue(element);
        element = list->proxy;
    }

    free(list);
}

// Swaps two elements in the list by their indices
void List_SwapElements(List *list, unsigned int index1, unsigned int index2){
    if(index1 >= List_Size(list) || index2 >= List_Size(list)){
        fprintf(stderr, "Index out of bounds\n");
        return;
    }

    // Ensure index1 < index2 for consistent logic
    if(index1 > index2){
        unsigned int temp = index1;
        index1 = index2;
        index2 = temp;
    }

    int isAdjacents = (index2 - index1 == 1);

    Element *element1 = List_GetElementOfIndex(list, index1);
    Element *element2 = List_GetElementOfIndex(list, index2);

    if(element1 == element2){
        return; // Nothing to swap
    }

    Element *prev1 = Element_GetPrevious(element1);
    Element *next1 = Element_Next(element1);
    Element *prev2 = Element_GetPrevious(element2);
    Element *next2 = Element_Next(element2);

    Element_SetNext(element1, next2);
    if(next2 != NULL){
        Element_SetPrevious(next2, element1);
    }
    Element_SetPrevious(element2, prev1);
    if(prev1 == NULL){
        list->proxy = element2; // Update head if element1 was first
    }
    else{
        Element_SetNext(prev1, element2);
    }

    if(isAdjacents){
        Element_SetNext(element2, element1);
        Element_SetPrevious(element1, element2);
    }
    else{
        Element_SetNext(element2, next1);
        if(next1 != NULL){
            Element_SetPrevious(next1, element2);
        }
        Element_SetPrevious(element1, prev2);
        Element_SetNext(prev2, element1);
    }
}

// Append an element to the end of the list
void List_Append(List *list, Element *element){
    Element *lastElement = List_GetLastElement(list);
    if(lastElement != NULL){
        Element_SetNext(lastElement, element);
        Element_SetPrevious(element, lastElement);
    }
    else{
        list->proxy = element; // First element in the list
    }

    list->size++;
}

// Insert an element at the beginning of the list
void List_Push(List *list, Element *element) {
    Element *firstElement = List_GetFirstElement(list);
    if (firstElement == NULL) {
        list->proxy = element;
    } else {
        Element_SetNext(element, firstElement);
        Element_SetPrevious(firstElement, element);
        list->proxy = element;
    }

    list->size++;
}

// Insert element at specific index in the list
void List_Insert(List *list, Element *element, unsigned int index){
    if(index > List_Size(list)){
        fprintf(stdout, "Index out of bounds\n");
        return;
    }

    if (index == List_Size(list)) {
        List_Append(list, element);
        return;
    }

    Element *oldElement = List_GetElementOfIndex(list, index);
    Element *prevElement = Element_GetPrevious(oldElement);

    Element_SetNext(element, oldElement);
    Element_SetPrevious(element, prevElement);
    Element_SetPrevious(oldElement, element);

    if(prevElement == NULL){
        list->proxy = element; // Inserting at the start
    }
    else{
        Element_SetNext(prevElement, element);
    }   

    list->size++;
}

// Remove element at given index from the list
void List_RemoveAt(List *list, unsigned int index){
    if(index >= List_Size(list)){
        fprintf(stdout, "Index out of bounds\n");
        return;
    }

    Element *element = List_GetElementOfIndex(list, index);
    Element *previousElement = Element_GetPrevious(element);
    Element *nextElement = Element_Next(element);

    if(previousElement != NULL){
        Element_SetNext(previousElement, nextElement);
    }
    else{
        list->proxy = nextElement; // Removing first element
    }

    if(nextElement != NULL){
        Element_SetPrevious(nextElement, previousElement);
    }

    Element_Destroy(element);
    list->size--;
}

// Returns current list size
unsigned int List_Size(List *list){
    return list->size;
}

// Utility for type system – counts elements in list without trusting the stored size
unsigned int List_CountSize(void *self){
    unsigned int size = 0;
    List *list = (List*)self;

    Element *element = list->proxy;
    while (element != NULL){
        size++;
        element = Element_Next(element);
    }

    return size;
}

// Print all elements in the list
void List_Print(List *list){
    Element *element = List_GetFirstElement(list);
    printf("Size: %d -> ", List_Size(list));
    while (element != NULL){
        Element_Print(element);
        printf(" ");
        element = Element_Next(element);
    }
    printf("\n");
}

// Get first element in list
Element *List_GetFirstElement(List *list){
    return list->proxy;
}

// Get last element in list
Element *List_GetLastElement(List *list){
    Element *lastElement = List_GetFirstElement(list);

    if(lastElement == NULL){
        return NULL;
    }

    while(Element_Next(lastElement) != NULL){
        lastElement = Element_Next(lastElement);
    }

    return lastElement;
}

// Get element at a specific index
Element *List_GetElementOfIndex(List *list, unsigned int index){
    if(index >= List_Size(list)){
        fprintf(stderr, "Index [%u] out of bounds\n", index);
        return NULL;
    }

    Element *elementOfIndex = List_GetFirstElement(list);
    for(unsigned int i = 0; i < index; i++){
        elementOfIndex = Element_Next(elementOfIndex);
    }

    return elementOfIndex;
}

// GENERIC TYPE SUPPORT BELOW

#include "typeManager.h"

// Type action: destroy a list instance through generic type system
Data **List_TypeDestroy(Data **data) {
    List *typeVariable = Data_GetList(*data);
    List_Destroy(typeVariable);
    return NULL;
}

// Type action: print a list via generic type system
Data **List_TypePrint(Data **data) {
    List *typeVariable = Data_GetList(*data);
    List_Print(typeVariable);
    return data;
}

// Register "list" type and its actions with the type system
void List_InitializeType() {
    Type *listType = Type_New("list");
    Type_Add(listType);

    TypeAction_Create("set", "list", Type_DefaultSetValue);
    TypeAction_Create("destroy", "list", List_TypeDestroy);
    TypeAction_Create("print", "list", List_TypePrint);
}

// Helper for element data access when it stores a list
List *Element_GetListData(Element *element){
    return Data_GetList(Element_GetData(element));
}

// Extract List from Data
List *Data_GetList(Data *data){
    return (List*)Data_GetValue(data);
}
