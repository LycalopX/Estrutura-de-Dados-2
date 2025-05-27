#include <stdio.h>

#include "operation.h"

int UseOperation(int a, int b, int *state, Operation *operation) {
    return operation->operation(a, b, state);
}

void PrintOperation(const Operation *operation) {
    printf("%c", operation->operationChar);
}

int Sum(int a, int b, int *state) {
    *state = 1;
    return a + b;
}

int Sub(int a, int b, int *state) {
    *state = 1;
    return a - b;
}

int Mul(int a, int b, int *state) {
    *state = 1;
    return a * b;
}

int Div(int a, int b, int *state) {
    // Division by zero
    if (b == 0) {
        *state = 0;
        return 1; 
    }
    *state = 1;
    return a / b;
}