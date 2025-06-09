#ifndef OPERATION_H
#define OPERATION_H

// Data structure to represent an operation
typedef struct {
    int (*operation)(int, int, int *);
    char operationChar;
} Operation;

// Uses the operation on a and b
int UseOperation(int a, int b, int *state, Operation *operation);
// Print the operation symbol
void PrintOperation(const Operation *operation);

// Basic operations
// State: 1 = success, 0 = failure
// a + b
int Sum(int a, int b, int *state);
// a - b
int Sub(int a, int b, int *state);
// a * b
int Mul(int a, int b, int *state);
// a / b
int Div(int a, int b, int *state);

#endif