#include <stdlib.h>
#include <stdio.h>

#include "list.h"

List *List_New(){
    List *newList = malloc(sizeof(List) * 1);
    newList->proxy = NULL;
    newList->size = 0;
    return newList;
}

void List_Destroy(List *list){
    Element *element = List_GetFirstElement(list);
    while(element != NULL){
        list->proxy = Element_Next(element);
        Element_Destroy(element);
        element = list->proxy;
    }

    free(list);
}

void List_DestroyWithoutElements(List *list){
    free(list);
}

void List_DestroyWithoutElementsData(List *list){
    Element *element = List_GetFirstElement(list);
    while(element != NULL){
        list->proxy = Element_Next(element);
        Element_DestroyWithoutData(element);
        element = list->proxy;
    }

    free(list);
}

void List_DestroyWithoutElementsDataValue(List *list){
    Element *element = List_GetFirstElement(list);
    while(element != NULL){
        list->proxy = Element_Next(element);
        Element_DestroyWithoutDataValue(element);
        element = list->proxy;
    }

    free(list);
}

void List_SwapElements(List *list, unsigned int index1, unsigned int index2){
    // Validation of indices
    if(index1 >= List_Size(list) || index2 >= List_Size(list)){
        fprintf(stderr, "Index out of bounds\n");
        return;
    }

    // Order indexes to ensure index1 < index2
    if(index1 > index2){
        unsigned int temp = index1;
        index1 = index2;
        index2 = temp;
    }

    int isAdjacents = (index2 - index1 == 1);

    Element *element1 = List_GetElementOfIndex(list, index1);
    Element *element2 = List_GetElementOfIndex(list, index2);

    // No need to swap if both indices point to the same element
    if(element1 == element2){
        return;
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
    // First element of the list
    if(prev1 == NULL){
        list->proxy = element2;
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

void List_Append(List *list, Element *element){
    Element *lastElement = List_GetLastElement(list);
    if(lastElement != NULL){
        Element_SetNext(lastElement, element);
        Element_SetPrevious(element, lastElement);
    }
    else{
        list->proxy = element;
    }

    list->size++;
}

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

void List_Insert(List *list, Element *element, unsigned int index){
    if(index > List_Size(list)){
        fprintf(stdout, "Index out of bounds\n");
        return;
    }

    // End of the list
    if (index == List_Size(list)) {
        List_Append(list, element);
        return;
    }

    Element *oldElement = List_GetElementOfIndex(list, index);
    Element *prevElement = Element_GetPrevious(oldElement);

    Element_SetNext(element, oldElement);
    Element_SetPrevious(element, prevElement);
    Element_SetPrevious(oldElement, element);

    // First element of the list
    if(prevElement == NULL){
        list->proxy = element; 
    }
    else{
        Element_SetNext(prevElement, element);
    }   

    list->size++;
}

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
        list->proxy = nextElement;
    }

    if(nextElement != NULL){
        Element_SetPrevious(nextElement, previousElement);
    }

    Element_Destroy(element);
    list->size--;
}

unsigned int List_Size(List *list){
    return list->size;
}

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

Element *List_GetFirstElement(List *list){
    return list->proxy;
}

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

// GENERIC
#include "typeManager.h"
Data **List_TypeDestroy(Data **data) {
    List *typeVariable = Data_GetList(*data);
    List_Destroy(typeVariable);
    return NULL;
}

Data **List_TypePrint(Data **data) {
    List *typeVariable = Data_GetList(*data);
    List_Print(typeVariable);
    return data;
}

void List_InitializeType() {
    Type *listType = Type_New("list");
    Type_Add(listType);

    TypeAction_Create("set", "list", Type_DefaultSetValue);
    TypeAction_Create("destroy", "list", List_TypeDestroy);
    TypeAction_Create("print", "list", List_TypePrint);
}

List *Element_GetListData(Element *element){
    return Data_GetList(Element_GetData(element));
}

List *Data_GetList(Data *data){
    return (List*)Data_GetValue(data);
}