#include <stdlib.h>

#include "element.h"

Element *Element_New(char *type, void *value){
    Data *newElementData = Data_New(type);
    if(newElementData == NULL){
        return NULL;
    }
    Element *newElement = Element_NewWithoutData();

    Data_SetValue(newElementData, value);
    Element_SetData(newElement, newElementData);

    return newElement;
}

Element *Element_NewWithoutData(){
    Element *newElement = malloc(sizeof(Element) * 1);
    newElement->next = NULL;
    newElement->previous = NULL;
    newElement->data = NULL;

    return newElement;
}

Element *Element_Copy(Element *element){
    if(element == NULL){
        return NULL;
    }

    Element *newElement = Element_NewWithoutData();
    Data *dataCopy = Element_GetData(element);
    Element_SetData(newElement, dataCopy);
    
    return newElement;
}

void Element_Destroy(Element *element){
    if(element->data != NULL){
        Data_Destroy(element->data);
    }
    
    free(element);
}

void Element_DestroyWithoutData(Element *element){
    free(element);
}

void Element_DestroyWithoutDataValue(Element *element){
    if(element->data != NULL){
        Data_DestroyWithoutValue(element->data);
    }

    free(element);
}

void Element_SetNext(Element *element, Element *proxy){
    element->next = proxy;
}

void Element_SetPrevious(Element *element, Element *proxy){
    element->previous = proxy;
}

Element *Element_Next(Element *element){
    return element->next;
}

Element *Element_GetPrevious(Element *element){
    return element->previous;
}

void Element_SetData(Element *element, Data *data){
    Data *oldData = Element_GetData(element);
    if(oldData != NULL){
        Data_Destroy(oldData);
    }
    element->data = data;
}

void Element_SetDataWithoutDestroy(Element *element, Data *data){
    element->data = data;
}

void Element_CopyData(Element *element, Element *sourceElement){
    Data *sourceData = Element_GetData(sourceElement);
    Element_SetData(element, sourceData);
}

void Element_SetDataValue(Element *element, void *value){
    Data_SetValue(Element_GetData(element), value);
}

void Element_SetDataValueWithoutDestroy(Element *element, void *value){
    Data_SetValueWithoutDestroy(Element_GetData(element), value);
}

Data *Element_GetData(Element *element){
    return element->data;
}

void *Element_GetDataValue(Element *element){
    return Data_GetValue(Element_GetData(element));
}

void Element_Print(Element *element){
    Data_Print(Element_GetData(element));
}

// Generic gets
int Element_GetIntData(Element *element){
    return Data_GetInt(Element_GetData(element));
}

float Element_GetFloatData(Element *element){
    return Data_GetFloat(Element_GetData(element));
}

double Element_GetDoubleData(Element *element){
    return Data_GetDouble(Element_GetData(element));
}

char Element_GetCharData(Element *element){
    return Data_GetChar(Element_GetData(element));
}

char *Element_GetStringData(Element *element){
    return Data_GetString(Element_GetData(element));
}