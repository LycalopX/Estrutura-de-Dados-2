#ifndef __ELEMENT_H__
#define __ELEMENT_H__

#include "data.h"

typedef struct{
    Data *data;
    void *next;
    void *previous;
} Element;

/**
 * @brief Creates a new Element with the specified type and value
 * 
 * @param type The type of the element
 * @param value The value of the element
 * @return A pointer to the newly created Element
 */
Element *Element_New(char *type, void *value);

/**
 * @brief Creates a new Element without any data
 * 
 * @return A pointer to the newly created Element
 */
Element *Element_NewWithoutData();

/**
 * @brief Creates a copy of an Element but uses the same data pointer
 * 
 * @param element The Element to be copied
 * @return A pointer to the newly created Element copy
 */
Element *Element_Copy(Element *element);

/**
 * @brief Creates a copy of an Element
 * 
 * @param element The Element to be copied
 * @return A pointer to the newly created Element copy
 */
Element *Element_Copy(Element *element);

/**
 * @brief Destroys an Element and its data
 * 
 * @param element The Element to be destroyed
 */
void Element_Destroy(Element *element);

/**
 * @brief Destroys an Element without destroying its data
 * 
 * @param element The Element to be destroyed
 */
void Element_DestroyWithoutData(Element *element);

/**
 * @brief Destroys an Element without destroying its data value
 * 
 * @param element The Element to be destroyed
 */
void Element_DestroyWithoutDataValue(Element *element);

/**
 * @brief Sets the next Element in the linked list
 * 
 * @param element The current Element
 * @param proxy The next Element to be set
 */
void Element_SetNext(Element *element, Element *proxy);

/**
 * @brief Sets the previous Element in the linked list
 * 
 * @param element The current Element
 * @param proxy The previous Element to be set
 */
void Element_SetPrevious(Element *element, Element *proxy);


/**
 * @brief Gets the next Element in the linked list
 * 
 * @param element The current Element
 * @return A pointer to the next Element
 */
Element *Element_Next(Element *element);

/**
 * @brief Gets the previous Element in the linked list
 * 
 * @param element The current Element
 * @return A pointer to the previous Element
 */
Element *Element_GetPrevious(Element *element);


/**
 * @brief Sets the data for the Element
 * 
 * @param element The Element to set data for
 * @param data The Data to be set
 */
void Element_SetData(Element *element, Data *data);

/**
 * @brief Sets the data for the Element without destroying the previous data
 * 
 * @param element The Element to set data for
 * @param data The Data to be set
 */
void Element_SetDataWithoutDestroy(Element *element, Data *data);

/**
 * @brief Copies the data from one Element to another
 * 
 * @param element The Element to copy data to
 * @param sourceElement The Element to copy data from
 */
void Element_CopyData(Element *element, Element *sourceElement);

/**
 * @brief Sets the value of the Element's data
 * 
 * @param element The Element to set data value for
 * @param value The value to be set
 */
void Element_SetDataValue(Element *element, void *value);

/**
 * @brief Sets the value of the Element's data without destroying the previous value
 * 
 * @param element The Element to set data value for
 * @param value The value to be set
 */
void Element_SetDataValueWithoutDestroy(Element *element, void *value);

/**
 * @brief Gets the data of the Element
 * 
 * @param element The Element to get data from
 * @return A pointer to the Data of the Element
 */
Data *Element_GetData(Element *element);

/**
 * @brief Gets the data value of the Element
 * 
 * @param element The Element to get data value from
 * @return A pointer to the data value of the Element
 */
void *Element_GetDataValue(Element *element);

/**
 * @brief Prints the Element's data
 * 
 * @param element The Element to be printed
 */
void Element_Print(Element *element);

// Generic gets - user needs to add more if needed
/*Example:
-Type- Element_Get-Type-Data(Element *element){
    return *(-Type-*)GetElementData(element)->value;
}
*/
int Element_GetIntData(Element *element);
float Element_GetFloatData(Element *element);
double Element_GetDoubleData(Element *element);
char Element_GetCharData(Element *element);
char *Element_GetStringData(Element *element);

#endif