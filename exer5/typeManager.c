#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "typeManager.h"
#include "data.h"

// Create a new Type
Type *Type_New(char *name) {
    // Stop if the type already exists
    if (Type_Get(name) != NULL) {
        printf("Error: Type (%s) already defined\n", name);
        return NULL;
    }

    Type *newType = malloc(sizeof(Type));

    // Allocate memory for type name
    newType->name = strdup(name); 
    
    return newType;
}

// Free a Type instance
void Type_Destroy(Type *type) {
    if (type != NULL) {
        free(type->name);
        free(type);
    }
}

// Default "set value" function for all basic types
// data[0] is the target, data[1] is the value to assign
Data **Type_DefaultSetValue(Data **data) {
    data[0]->value = data[1]->value;  
    return data;
}

// Default "destroy" function for basic types
Data **Type_DefaultDestroyValue(Data **data) {
    free(Data_GetValue(*data));
    return data;
}

// Default print functions
Data **Int_PrintData(Data **data){
    printf("%d", *(int *)(*data)->value);
    return data;
}

Data **Float_PrintData(Data **data){
    printf("%f", *(float *)(*data)->value);
    return data;
}

Data **Char_PrintData(Data **data){
    printf("%c", *(char *)(*data)->value);
    return data;
}

Data **Double_PrintData(Data **data){
    printf("%f", *(double *)(*data)->value);
    return data;
}

Data **String_PrintData(Data **data){
    printf("%s", (char *)(*data)->value);
    return data;
}

// Type registry
Type **typeList = NULL;
int typeListCount = 0;
int typeListSpace = 10;

// Add a new Type to the list
void Type_Add(Type *newType) {
    if (typeListCount >= typeListSpace) {
        typeListSpace *= 2;
        Type **newTypeList = realloc(typeList, typeListSpace * sizeof(Type *));
        if (newTypeList == NULL) {
            typeListSpace /= 2;
            printf("Error: Failed to allocate memory for typeList\n");
            return;
        }
        typeList = newTypeList;
    }

    typeList[typeListCount] = newType;
    typeListCount++;
}

// Automatically initialize basic types at program startup
__attribute__((constructor))
void InitializeBasicTypes() {
    typeList = malloc(sizeof(Type *) * typeListSpace);
    if (typeList == NULL) {
        printf("Error: Failed to allocate memory for typeList\n");
        return;
    }
    
    Type *intType = Type_New("int");
    Type *floatType = Type_New("float");
    Type *charType = Type_New("char");
    Type *stringType = Type_New("string");

    Type_Add(intType);
    Type_Add(floatType);
    Type_Add(charType);
    Type_Add(stringType);
}

// Automatically clean up all types at program exit
__attribute__((destructor))
void DestroyAllTypes() {
    for (int i = 0; i < typeListCount; i++) {
        Type_Destroy(typeList[i]);
    }

    free(typeList);
}

// Get Type by name
Type *Type_Get(char *type) {
    for (int i = 0; i < typeListCount; i++) {
        if (typeList[i] && typeList[i]->name && strcmp(typeList[i]->name, type) == 0) {
            return typeList[i];
        }
    }

    return NULL;
}

// Get the Type of a Data
Type *Type_GetData(Data *data) {
    return Type_Get(data->type);
}

// Get the name of a Type
char *Type_GetName(Type *type){
    return type->name;
}

// ---------------------------
// Comparison functions
// ---------------------------

// Default int-to-int comparison
int CompareData_int_int(Data *data1, Data *data2){
    if(Data_GetInt(data1) > Data_GetInt(data2)) return 1;
    else if(Data_GetInt(data1) < Data_GetInt(data2)) return -1;
    else return 0;
}

// Default char-to-char comparison
int CompareData_char_char(Data *data1, Data *data2){
    if(Data_GetChar(data1) > Data_GetChar(data2)) return 1;
    else if(Data_GetChar(data1) < Data_GetChar(data2)) return -1;
    else return 0;
}

// Comparison registry
CompareFunction **compareFunctionList = NULL;
int compareFunctionListSpace = 10;
int compareFunctionListCount = 0;

// Create new CompareFunction
CompareFunction *CompareFunction_New(char *type1, char *type2, int (*compareFunction)(Data*, Data*)){
    CompareFunction *newCompareFunction = malloc(sizeof(CompareFunction));
    newCompareFunction->id = malloc(strlen(type1) + strlen(type2) + 2);
    newCompareFunction->id = ConvertTypesNamesToCompareId(newCompareFunction->id, type1, type2);
    newCompareFunction->compareFunction = compareFunction;

    return newCompareFunction;
}

// Free a CompareFunction
void CompareFunction_Destroy(CompareFunction *compareFunction){
    if (compareFunction != NULL) {
        free(compareFunction->id);
        free(compareFunction);
    }
}

// Add CompareFunction to list
void CompareFunction_Add(CompareFunction *newCompareFunction){
    if (compareFunctionListCount >= compareFunctionListSpace) {
        compareFunctionListSpace *= 2;
        CompareFunction **newList = realloc(compareFunctionList, compareFunctionListSpace * sizeof(CompareFunction *));
        if (newList == NULL) {
            compareFunctionListSpace /= 2;
            printf("Error: Failed to allocate memory for compareFunctionList\n");
            return;
        }
        compareFunctionList = newList;
    }

    compareFunctionList[compareFunctionListCount++] = newCompareFunction;
}

// Retrieve CompareFunction by id
CompareFunction *CompareFunction_GetById(char *id){
    for(int i = 0; i < compareFunctionListCount; i++){
        if(strcmp(compareFunctionList[i]->id, id) == 0){
            return compareFunctionList[i];
        }
    }
    return NULL;
}

// Automatically initialize compare functions
__attribute__((constructor))
void InitializeBasicCompareFunctions() {
    compareFunctionList = malloc(sizeof(CompareFunction *) * compareFunctionListSpace);
    if (compareFunctionList == NULL) {
        printf("Error: Failed to allocate memory for compareFunctionList\n");
        return;
    }

    CompareFunction_Add(CompareFunction_New("int", "int", CompareData_int_int));
    CompareFunction_Add(CompareFunction_New("char", "char", CompareData_char_char));
}

// Automatically clean up compare functions
__attribute__((destructor))
void DestroyAllComapareFunctions(){
    for(int i = 0; i < compareFunctionListCount; i++){
        CompareFunction_Destroy(compareFunctionList[i]);
    }

    free(compareFunctionList);
}

// Build a compare function ID from types
char *ConvertTypesNamesToCompareId(char *id, char *type1, char *type2){
    strcpy(id, type1);
    strcat(id, "_");
    strcat(id, type2);
    return id;
}

// Build a compare function ID from two Data objects
char *ConvertDataToCompareId(char *id, Data *data1, Data *data2){
    return ConvertTypesNamesToCompareId(id, Data_GetTypeName(data1), Data_GetTypeName(data2));
}

// Compare two Data values using registered functions
int Data_Compare(Data *data1, Data *data2){
    if(data1 == data2) return 0;

    if(data1 == NULL || data2 == NULL) {
        printf("Error: One data is NULL\n");
        return -1;
    }

    char *id = malloc(strlen(data1->type) + strlen(data2->type) + 2);
    ConvertDataToCompareId(id, data1, data2);
    CompareFunction *compareFunction = CompareFunction_GetById(id);

    if(compareFunction == NULL){
        // Try reversed types
        Data *tmp = data1;
        data1 = data2;
        data2 = tmp;

        ConvertDataToCompareId(id, data1, data2);
        compareFunction = CompareFunction_GetById(id);

        if(compareFunction == NULL){
            printf("Error: Compare function not found for types %s\n", id);
            free(id);
            return 0;
        }
    }

    free(id);
    return compareFunction->compareFunction(data1, data2);
}

// ---------------------------
// Type actions
// ---------------------------

// Create a new TypeAction
TypeAction *TypeAction_New(char *name, char *type, Action *action){
    if(name == NULL || type == NULL || action == NULL) {
        printf("Error: Invalid parameters for TypeAction_New\n");
        return NULL;
    }
    if(TypeAction_Get(name, type) != NULL) {
        printf("Error: Type action (%s, %s) already exists\n", name, type);
        return NULL;
    }

    TypeAction *newTypeAction = malloc(sizeof(TypeAction));
    newTypeAction->name = strdup(name);
    newTypeAction->type = strdup(type);
    newTypeAction->action = action;

    return newTypeAction;
}

// Free a TypeAction
void TypeAction_Destroy(TypeAction *typeAction){
    if (typeAction != NULL) {
        free(typeAction->name);
        free(typeAction->type);
        free(typeAction);
    }
}

// Add a TypeAction to the list
int TypeAction_Add(TypeAction *newTypeAction){
    if (typeActionListCount >= typeActionListSpace) {
        typeActionListSpace *= 2;
        TypeAction **newList = realloc(typeActionList, typeActionListSpace * sizeof(TypeAction *));
        if (newList == NULL) {
            typeActionListSpace /= 2;
            printf("Error: Failed to allocate memory for typeActionFuncionList\n");
            return 0;
        }
        typeActionList = newList;
    }

    typeActionList[typeActionListCount++] = newTypeAction;
    return 1;
}

// Create and add a TypeAction
int TypeAction_Create(char *name, char *type, Action *action) {
    TypeAction *newTypeAction = TypeAction_New(name, type, action);
    if (newTypeAction == NULL) {
        printf("Error: Failed to create type action (%s, %s)\n", name, type);
        return -1;
    }
    TypeAction_Add(newTypeAction);
    return 0;
}

// TypeAction registry
TypeAction **typeActionList = NULL;
int typeActionListSpace = 30;
int typeActionListCount = 0;

// Initialize basic type actions
__attribute__((constructor))
void InitializeBasicTypeActions() {
    typeActionList = malloc(sizeof(TypeAction *) * typeActionListSpace);
    if (typeActionList == NULL) {
        printf("Error: Failed to allocate memory for typeActionFuncionList\n");
        return;
    }

    // Set
    TypeAction_Create("set", "int", Type_DefaultSetValue);
    TypeAction_Create("set", "float", Type_DefaultSetValue);
    TypeAction_Create("set", "char", Type_DefaultSetValue);
    TypeAction_Create("set", "double", Type_DefaultSetValue);
    TypeAction_Create("set", "string", Type_DefaultSetValue);

    // Print
    TypeAction_Create("print", "int", Int_PrintData);
    TypeAction_Create("print", "float", Float_PrintData);
    TypeAction_Create("print", "char", Char_PrintData);
    TypeAction_Create("print", "double", Double_PrintData);
    TypeAction_Create("print", "string", String_PrintData);

    // Destroy
    TypeAction_Create("destroy", "int", Type_DefaultDestroyValue);
    TypeAction_Create("destroy", "float", Type_DefaultDestroyValue);
    TypeAction_Create("destroy", "char", Type_DefaultDestroyValue);
    TypeAction_Create("destroy", "double", Type_DefaultDestroyValue);
    TypeAction_Create("destroy", "string", Type_DefaultDestroyValue);
}

// Clean up type actions
__attribute__((destructor))
void DestroyAllTypeActions(){
    for(int i = 0; i < typeActionListCount; i++){
        TypeAction_Destroy(typeActionList[i]);
    }

    free(typeActionList);
}

// Get a TypeAction by name and type
TypeAction *TypeAction_Get(char *name, char *type){
    for (int i = 0; i < typeActionListCount; i++) {
        if (typeActionList[i] != NULL &&
            strcmp(typeActionList[i]->name, name) == 0 &&
            strcmp(typeActionList[i]->type, type) == 0) {
            return typeActionList[i];
        }
    }

    return NULL;
}

// Get the action from a TypeAction
Action *TypeAction_GetAction(TypeAction *typeAction) {
    if (typeAction == NULL) {
        printf("Error: Type action can't be NULL\n");
        return NULL;
    }

    return typeAction->action;
}

// Use a TypeAction with a type and data
Data **TypeAction_UseAction(char *name, char *type, Data **data){
    TypeAction *typeAction = TypeAction_Get(name, type);
    if (typeAction == NULL) {
        printf("Error: Type action (%s, %s) not found\n", name, type);
        return NULL;
    }

    Action *action = TypeAction_GetAction(typeAction);
    if (action == NULL) {
        printf("Error: Action (%s, %s) not found\n", name, type);
        return NULL;
    }

    return action(data);
}

// Shortcut for single-data input
Data **TypeAction_UseActionMonoData(char *name, Data *data){
    return TypeAction_UseAction(name, data->type, &data);
}

// Modify an existing action
int TypeAction_EditAction(char *name, char *type, Action *newAction) {
    TypeAction *typeAction = TypeAction_Get(name, type);
    if (typeAction == NULL) {
        printf("Error: Type action (%s, %s) not found\n", name, type);
        return -1;
    }

    typeAction->action = newAction;
    return 0;
}
