#ifndef __DATA_H__
#define __DATA_H__

typedef struct{
    void *value;
    char *type;
} Data;

#include "typeManager.h"

/**
 * @brief Creates a new Data object with the specified type
 * 
 * @param type The type of the data
 * @return A pointer to the newly created Data object, or NULL if the type does not exist
 */
Data *Data_New(char *type);

/**
 * @brief Creates a temporary Data object with a specified value
 * 
 * @param value The value to be stored in the temporary Data object
 * @return A Data object containing the specified value
 */
Data Data_TemporaryData(void *value);

/**
 * @brief Destroys a Data object without destroying its value
 * 
 * @param data The Data object to be destroyed
 */
void Data_DestroyWithoutValue(Data *data);

/**
 * @brief Destroys a Data object and its value
 * 
 * @param data The Data object to be destroyed
 */
void Data_Destroy(Data *data);

/**
 * @brief Destroys the value of a Data object without destroying the object itself
 * 
 * @param data The Data object whose value is to be destroyed
 */
void Data_DestroyValue(Data *data);

/**
 * @brief Gets the name of the type of a Data object
 * 
 * @param data The Data object whose type name is to be retrieved
 * @return A string representing the type name of the Data object
 */
char *Data_GetTypeName(Data *data);

/**
 * @brief Gets the value of a Data object
 * 
 * @param data The Data object whose value is to be retrieved
 * @return A pointer to the value stored in the Data object
 */
void *Data_GetValue(Data *data);


/**
 * @brief Sets the value of a Data object without destroying its previous value
 * 
 * @param data The Data object to set the value for
 * @param value The new value to be set
 */
void Data_SetValueWithoutDestroy(Data *data, void *value);

/**
 * @brief Sets the value of a Data object, destroying its previous value if it exists
 * 
 * @param data The Data object to set the value for
 * @param value The new value to be set
 */
void Data_SetValue(Data *data, void *value);

/**
 * @brief Prints the value of a Data object
 * 
 * @param data The Data object to be printed
 */
void Data_Print(Data *data);


/**
 * @brief Gets the type of a Data object
 * 
 * @param data The Data object whose type is to be retrieved
 * @return A pointer to the Type object representing the type of the Data object
 */
Data **Data_UseActionMonoData(char *actionName, Data *data);

/**
 * @brief Uses a specified action on a Data object with a given type
 * 
 * @param actionName The name of the action to be performed
 * @param type The type of the Data object
 * @param data A pointer to an array of Data objects on which the action will be performed
 * @return A pointer to an array of Data objects after the action is performed, or NULL if the action does not exist
 */
Data **Data_UseAction(char *actionName, char *type, Data **data);

// Generic gets - user needs to add more if needed
/*Example:
-Type- Data_Get-Type-(Data *data){
    return *(-Type-*)GetDataValue(data);
}
*/
int Data_GetInt(Data *data);
float Data_GetFloat(Data *data);
double Data_GetDouble(Data *data);
char Data_GetChar(Data *data);
char *Data_GetString(Data *data);
#endif