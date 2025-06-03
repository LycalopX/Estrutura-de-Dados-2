#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "data.h"
#include "typeManager.h"

Data *Data_New(char *type){
    if(Type_Get(type) == NULL){
        fprintf(stderr, "Error: Type (%s) doesn't exist", type);
        return NULL;
    }
    
    Data *newData = malloc(sizeof(Data) * 1);

    //Check if type exists
    newData->type = strdup(type);
    newData->value = NULL;

    return newData;
}

Data Data_TemporaryData(void *value){
    Data temp;
    temp.type = NULL;
    temp.value = value;
    return temp;
}

void Data_DestroyWithoutValue(Data *data){
    if(data == NULL){
        return;
    }
    if(Data_GetTypeName(data) != NULL){
        free(data->type);
    }
    
    free(data);
}

void Data_Destroy(Data *data){
    if(data->value != NULL){
        Data_DestroyValue(data);
    }

    Data_DestroyWithoutValue(data);
}

void Data_DestroyValue(Data *data){
    if(data->value != NULL){
        Data_UseActionMonoData("destroy", data);
    }

    data->value = NULL;
}

void Data_SetValueWithoutDestroy(Data *data, void *value){
    Type *dataType = Type_Get(Data_GetTypeName(data));
    if(dataType == NULL){
        fprintf(stderr, "Error: Type (%s) doesn't exist", Data_GetTypeName(data));
        return;
    }

    Data tempData = Data_TemporaryData(value);
    if(Data_UseAction("set", Data_GetTypeName(data), ((Data*[]){data, &tempData})) == NO_FUNCTION){
        fprintf(stderr, "Error: Type (%s) doesn't have a set function", Data_GetTypeName(data));
        return;
    }
}

void Data_SetValue(Data *data, void *value){
    Data_DestroyValue(data);
    Data_SetValueWithoutDestroy(data, value);
}

void Data_Print(Data *data){
    Data **response = Data_UseActionMonoData("print", data);
    if(response == NULL){
        fprintf(stderr, "Error: Type (%s) doesn't have a print function", data->type);
        return;
    }
}

char *Data_GetTypeName(Data *data){
    return data->type;
}

void *Data_GetValue(Data *data){
    return data->value;
}

Data **Data_UseActionMonoData(char *actionName, Data *data) {
    return Data_UseAction(actionName, Data_GetTypeName(data), &data);
}

Data **Data_UseAction(char *actionName, char *type, Data **data) {
    TypeAction *typeAction = TypeAction_Get(actionName, type);
    if (typeAction == NULL) {
        fprintf(stderr, "Error: Type action (%s, %s) not found", actionName, type);
        return NULL;
    }

    Action *action = TypeAction_GetAction(typeAction);
    if (action == NULL) {
        fprintf(stderr, "Error: Action (%s, %s) not found", actionName, type);
        return NULL;
    }

    return action(data);
}

// Generic gets
int Data_GetInt(Data *data){
    return *(int*)Data_GetValue(data);
}

float Data_GetFloat(Data *data){
    return *(float*)Data_GetValue(data);
}

double Data_GetDouble(Data *data){
    return *(double*)Data_GetValue(data);
}

char Data_GetChar(Data *data){
    return *(char*)Data_GetValue(data);
}

char *Data_GetString(Data *data){
    return (char*)Data_GetValue(data);
}