#ifndef __EQUATION_H__
#define __EQUATION_H__

#include "operation.h"

// Data structure to represent an equation
typedef struct {
    // Array of inputs
    int *inputs;
    // Length of the inputs array
    unsigned inputsLength;
    // Array of operations
    unsigned inputsOperaionsLength;
    // Array of operations
    Operation *operations;
    // Length of the operations array
    unsigned operationsCount;
    // Array of operation indices
    unsigned *operationIndex;
} Equation;

// Print the equation
void PrintEquation(const Equation *equation);

// Get the value of the equation
// state = 1 if no error
int EquationValue(const Equation *equation, int *state);

// Gets the next equation combination
// Returns 0 if restart
// Returns 1 if next combination
int NextCombination(const Equation *equation);

// Tries to find the target value recursively
// Returns 1 if found
// Returns 0 if not found
int EquationTryFindTargetRecursive(const Equation *equation, int target, int *state, unsigned *calls);

// Tries to find the target value
// Returns 1 if found
// Returns 0 if not found
int EquationTryFindTarget(const Equation *equation, int target, unsigned *calls);

// Tries to find the target value from permutations
// Returns 1 if found
// Returns 0 if not found
int EquationTryFindTargetFromPermutations(Equation* eq, int target, unsigned* calls, int** permutations, unsigned total);

#endif