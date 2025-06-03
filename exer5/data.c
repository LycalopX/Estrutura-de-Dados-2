#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "data.h"
#include "typeManager.h"

// Creates a new Data object associated with a given type (string)
Data *Data_New(char *type){
    if(Type_Get(type) == NULL){
        // Ensure the type exists before creating the Data
        fprintf(stderr, "Error: Type (%s) doesn't exist", type);
        return NULL;
    }

    Data *newData = malloc(sizeof(Data) * 1); // Allocate memory for the new Data

    newData->type = strdup(type); // Store a copy of the type name
    newData->value = NULL;        // Initially no value is assigned

    return newData; // Return the newly created Data object
}

// Creates a temporary Data object (not heap-allocated), only stores a value without a type
Data Data_TemporaryData(void *value){
    Data temp;
    temp.type = NULL;
    temp.value = value;
    return temp;
}

// Frees only the Data struct and type name string, does not destroy the internal value
void Data_DestroyWithoutValue(Data *data){
    if(data == NULL){
        return;
    }
    if(Data_GetTypeName(data) != NULL){
        free(data->type); // Free the duplicated type name string
    }

    free(data); // Free the Data struct itself
}

// Fully destroys the Data object, including its value and type
void Data_Destroy(Data *data){
    if(data->value != NULL){
        Data_DestroyValue(data); // First destroy the stored value (via action)
    }

    Data_DestroyWithoutValue(data); // Then free the Data struct
}

// Destroys only the internal value (via the "destroy" action)
void Data_DestroyValue(Data *data){
    if(data->value != NULL){
        Data_UseActionMonoData("destroy", data); // Call the custom "destroy" function for this type
    }

    data->value = NULL;
}

// Sets a new value to Data without destroying the previous one (dangerous if leaks aren't managed)
void Data_SetValueWithoutDestroy(Data *data, void *value){
    Type *dataType = Type_Get(Data_GetTypeName(data));
    if(dataType == NULL){
        fprintf(stderr, "Error: Type (%s) doesn't exist", Data_GetTypeName(data));
        return;
    }

    // Wrap the new value in a temporary Data struct
    Data tempData = Data_TemporaryData(value);

    // Call the "set" action for the type, passing both the Data and the new value
    if(Data_UseAction("set", Data_GetTypeName(data), ((Data*[]){data, &tempData})) == NO_FUNCTION){
        fprintf(stderr, "Error: Type (%s) doesn't have a set function", Data_GetTypeName(data));
        return;
    }
}

// Sets a new value to Data, destroying the previous one if it exists
void Data_SetValue(Data *data, void *value){
    Data_DestroyValue(data);                // Free existing value
    Data_SetValueWithoutDestroy(data, value); // Set new value
}

// Calls the "print" action on the Data, which should be defined by the type
void Data_Print(Data *data){
    Data **response = Data_UseActionMonoData("print", data);
    if(response == NULL){
        fprintf(stderr, "Error: Type (%s) doesn't have a print function", data->type);
        return;
    }
}

// Returns the type name of the Data
char *Data_GetTypeName(Data *data){
    return data->type;
}

// Returns the stored value of the Data
void *Data_GetValue(Data *data){
    return data->value;
}

// Calls an action that operates on a single Data pointer (helper)
Data **Data_UseActionMonoData(char *actionName, Data *data) {
    return Data_UseAction(actionName, Data_GetTypeName(data), &data);
}

// Looks up and calls the appropriate action for a given type and action name
Data **Data_UseAction(char *actionName, char *type, Data **data) {
    TypeAction *typeAction = TypeAction_Get(actionName, type); // Get the registered type-action
    if (typeAction == NULL) {
        fprintf(stderr, "Error: Type action (%s, %s) not found", actionName, type);
        return NULL;
    }

    Action *action = TypeAction_GetAction(typeAction); // Get the actual function
    if (action == NULL) {
        fprintf(stderr, "Error: Action (%s, %s) not found", actionName, type);
        return NULL;
    }

    return action(data); // Call the action with the provided data
}

// --- Generic getters (type-specific conversions) ---

// Get value as int
int Data_GetInt(Data *data){
    return *(int*)Data_GetValue(data);
}

// Get value as float
float Data_GetFloat(Data *data){
    return *(float*)Data_GetValue(data);
}

// Get value as double
double Data_GetDouble(Data *data){
    return *(double*)Data_GetValue(data);
}

// Get value as char
char Data_GetChar(Data *data){
    return *(char*)Data_GetValue(data);
}

// Get value as string (char pointer)
char *Data_GetString(Data *data){
    return (char*)Data_GetValue(data);
}
