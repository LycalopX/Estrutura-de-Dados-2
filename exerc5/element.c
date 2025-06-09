#include <stdlib.h>
#include "element.h"

// Creates a new Element with a new Data object of the given type and value
Element *Element_New(char *type, void *value){
    Data *newElementData = Data_New(type); // Create a new Data structure with the given type
    if(newElementData == NULL){
        return NULL; // Return NULL if Data creation fails
    }
    Element *newElement = Element_NewWithoutData(); // Create a new empty Element

    Data_SetValue(newElementData, value); // Set the value inside the Data
    Element_SetData(newElement, newElementData); // Assign the Data to the Element

    return newElement; // Return the fully initialized Element
}

// Creates a new Element without any Data
Element *Element_NewWithoutData(){
    Element *newElement = malloc(sizeof(Element) * 1); // Allocate memory for one Element
    newElement->next = NULL; // Initialize pointers to NULL
    newElement->previous = NULL;
    newElement->data = NULL;

    return newElement; // Return the new empty Element
}

// Creates a shallow copy of an existing Element (shares the same Data)
Element *Element_Copy(Element *element){
    if(element == NULL){
        return NULL; // Return NULL if the input Element is NULL
    }

    Element *newElement = Element_NewWithoutData(); // Create a new empty Element
    Data *dataCopy = Element_GetData(element); // Get the Data from the original Element
    Element_SetData(newElement, dataCopy); // Set the same Data to the new Element (no deep copy)

    return newElement; // Return the copied Element
}

// Frees the Element and its associated Data
void Element_Destroy(Element *element){
    if(element->data != NULL){
        Data_Destroy(element->data); // Free the Data if it exists
    }

    free(element); // Free the Element itself
}

// Frees only the Element (not the associated Data)
void Element_DestroyWithoutData(Element *element){
    free(element);
}

// Frees the Element and the Data structure, but not the Data's internal value
void Element_DestroyWithoutDataValue(Element *element){
    if(element->data != NULL){
        Data_DestroyWithoutValue(element->data); // Only free the Data wrapper
    }

    free(element); // Free the Element itself
}

// Sets the 'next' pointer of an Element
void Element_SetNext(Element *element, Element *proxy){
    element->next = proxy;
}

// Sets the 'previous' pointer of an Element
void Element_SetPrevious(Element *element, Element *proxy){
    element->previous = proxy;
}

// Returns the 'next' Element in the list
Element *Element_Next(Element *element){
    return element->next;
}

// Returns the 'previous' Element in the list
Element *Element_GetPrevious(Element *element){
    return element->previous;
}

// Sets a new Data to the Element, destroying any old Data
void Element_SetData(Element *element, Data *data){
    Data *oldData = Element_GetData(element);
    if(oldData != NULL){
        Data_Destroy(oldData); // Free the old Data
    }
    element->data = data; // Assign the new Data
}

// Sets the Data without destroying the old one (used with caution)
void Element_SetDataWithoutDestroy(Element *element, Data *data){
    element->data = data;
}

// Copies the Data from one Element to another (shallow copy)
void Element_CopyData(Element *element, Element *sourceElement){
    Data *sourceData = Element_GetData(sourceElement);
    Element_SetData(element, sourceData);
}

// Sets the value of the Element's Data
void Element_SetDataValue(Element *element, void *value){
    Data_SetValue(Element_GetData(element), value);
}

// Sets the value of the Element's Data without destroying the previous value
void Element_SetDataValueWithoutDestroy(Element *element, void *value){
    Data_SetValueWithoutDestroy(Element_GetData(element), value);
}

// Returns the Data of the Element
Data *Element_GetData(Element *element){
    return element->data;
}

// Returns the actual value stored inside the Element's Data
void *Element_GetDataValue(Element *element){
    return Data_GetValue(Element_GetData(element));
}

// Prints the Element's Data (uses the Data_Print function)
void Element_Print(Element *element){
    Data_Print(Element_GetData(element));
}

// --- Generic type-safe accessors (assuming Data type is known) ---

// Returns the value as int
int Element_GetIntData(Element *element){
    return Data_GetInt(Element_GetData(element));
}

// Returns the value as float
float Element_GetFloatData(Element *element){
    return Data_GetFloat(Element_GetData(element));
}

// Returns the value as double
double Element_GetDoubleData(Element *element){
    return Data_GetDouble(Element_GetData(element));
}

// Returns the value as char
char Element_GetCharData(Element *element){
    return Data_GetChar(Element_GetData(element));
}

// Returns the value as string (char *)
char *Element_GetStringData(Element *element){
    return Data_GetString(Element_GetData(element));
}
