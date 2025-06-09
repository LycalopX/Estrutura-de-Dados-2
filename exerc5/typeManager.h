#ifndef __TYPE_MANAGER_H__
#define __TYPE_MANAGER_H__

#include "data.h"

// Type
typedef struct {
    char *name;
} Type;

/**
 * @brief Creates a new type
 * 
 * @param name Type name
 */
Type *Type_New(char *name);

/**
 * @brief Destroys the type
 * 
 * @param type Type to be destroyed
 */
void Type_Destroy(Type *type);

#define NO_FUNCTION NULL
#define ROOT_TYPE NULL

// Basic functions
/**
 * @brief Sets the value of the data
 * 
 * @param data Datas, data[0] is the data to set, data[1] is the value to set
 * @return Data** Pointer to the data after the value is set
 */
Data **Type_DefaultSetValue(Data **data);

/**
 * @brief Destroys the data value
 * 
 * @param value Value to be destroyed
 * @return Data** Pointer to the data after the value is destroyed
 */
Data **Type_DefaultDestroyValue(Data **value);

// Default print functions
Data **Int_PrintData(Data **data);
Data **Float_PrintData(Data **data);
Data **Char_PrintData(Data **data);
Data **Double_PrintData(Data **data);
Data **String_PrintData(Data **data);

// typeList and typeCount
extern Type **typeList;
extern int typeListSpace;
extern int typeListCount;

/**
 * @brief Add type to valid types
 * 
 * @param value New type to be assigned
 */
void Type_Add(Type *newType);

/**
 * @brief Get the type of the string
 * 
 * @param value String to get the type from
 */
Type *Type_Get(char *type);

/**
 * @brief Get the type of the data
 * 
 * @param value Data to get the type from
 */
Type *Type_GetData(Data *data);

/**
 * @brief Get the name of the type
 * 
 * @param type Type to get the name from
 */
char *Type_GetName(Type *type);

// COMPARE FUNCTION
typedef struct{
    char *id;
    int (*compareFunction)(Data*, Data*);
} CompareFunction;

/**
 * @brief Creates a new compare function
 * 
 * @param type1 First type name
 * @param type2 Second type name
 * @param compareFunction Function to compare two data
 */
CompareFunction *CompareFunction_New(char *type1, char *type2, int (*compareFunction)(Data*, Data*));

/**
 * @brief Destroys the compare function
 * 
 * @param compareFunction Compare function to be destroyed
 */
void CompareFunction_Destroy(CompareFunction *compareFunction);

/**
 * @brief Adds a new compare function to the list
 * 
 * @param newCompareFunction New compare function to be added
 */
void CompareFunction_Add(CompareFunction *newCompareFunction);

/**
 * @brief Gets a compare function by its id
 * 
 * @param id Id of the compare function
 * @return CompareFunction* Pointer to the compare function, or NULL if not found
 */
CompareFunction *CompareFunction_GetById(char *id);

extern CompareFunction **compareFunctionList;
extern int compareFunctionListSpace;
extern int compareFunctionListCount;

/**
 * @brief Converts two type names to a compare id
 * 
 * @param id Id to be assigned
 * @param type1 First type name
 * @param type2 Second type name
 * @return char* Pointer to the id
 */
char *ConvertTypesNamesToCompareId(char *id, char *type1, char *type2);

/**
 * @brief Converts two data to a compare id
 * 
 * @param id Id to be assigned
 * @param data1 First data
 * @param data2 Second data
 * @return char* Pointer to the id
 */
char *ConvertDataToCompareId(char *id, Data *data1, Data *data2);

/**
 * @brief Compares two data
 * 
 * @param data1 First data to be compared
 * @param data2 Second data to be compared
 * @return int Result of the comparison: 1 if data1 > data2, -1 if data1 < data2, 0 if equal
 */
int Data_Compare(Data *data1, Data *data2);

// TYPE ACTIONS

typedef Data** (Action)(Data**);
typedef struct{
    char *name;
    char *type;
    Action *action;
} TypeAction;
extern TypeAction **typeActionList;
extern int typeActionListSpace;
extern int typeActionListCount;

/**
 * @brief Creates a new type action
 * 
 * @param name Name of the action
 * @param type Type of the action
 * @param action Action to be performed
 * @return TypeAction* Pointer to the new type action
 */
TypeAction *TypeAction_New(char *name, char *type, Action *action);

/**
 * @brief Destroys the type action
 * 
 * @param typeAction Type action to be destroyed
 */
void TypeAction_Destroy(TypeAction *typeAction);

/**
 * @brief Adds a new type action to the list
 * 
 * @param newTypeAction New type action to be added
 * @return int 0 if successful, -1 if the type action could not be added
 */
int TypeAction_Add(TypeAction *newTypeAction);

/**
 * @brief Creates a new type action and adds it to the list
 * 
 * @param name Name of the action
 * @param type Type of the action
 * @param action Action to be performed
 * @return int 0 if successful, -1 if the type action could not be created
 */
int TypeAction_Create(char *name, char *type, Action *action);

/**
 * @brief Gets a type action by its name and type
 * 
 * @param name Name of the action
 * @param type Type of the action
 * @return TypeAction* Pointer to the type action, or NULL if not found
 */
TypeAction *TypeAction_Get(char *name, char *type);

/**
 * @brief Gets the action of a type action
 * 
 * @param typeAction Type action to get the action from
 * @return Action* Pointer to the action, or NULL if not found
 */
Action *TypeAction_GetAction(TypeAction *typeAction);

/**
 * @brief Uses a type action by its name and type
 * 
 * @param name Name of the action
 * @param type Type of the action
 * @param data Data to be used with the action
 * @return Data** Pointer to the data after the action is performed, or NULL if not found
 */
Data **TypeAction_UseAction(char *name, char *type, Data **data);

/**
 * @brief Uses a type action by its name and mono data
 * 
 * @param name Name of the action
 * @param data Mono data to be used with the action
 * @return Data* Pointer to the data after the action is performed, or NULL if not found
 */
Data **TypeAction_UseActionMonoData(char *name, Data *data);

/**
 * @brief Edits an existing type action
 * 
 * @param name Name of the action to be edited
 * @param type Type of the action to be edited
 * @param newAction New action to be assigned
 * @return int 0 if successful, -1 if the type action was not found
 */
int TypeAction_EditAction(char *name, char *type, Action *newAction);

#endif