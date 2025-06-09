#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "equation.h"
#include "utilities.h"

// ERROR
#define TOO_MANY_ARGUMENTS_MESSAGE "Too many arguments\n"
#define TOO_MANY_ARGUMENTS 1
#define TOO_FEW_ARGUMENTS_MESSAGE "Too few arguments\n"
#define TOO_FEW_ARGUMENTS 2
#define INVALID_INPUT_MESSAGE "Invalid input\n"
#define INVALID_INPUT 3

// MESSAGES
#define NO_COMBINATION_FOUND_MESSAGE "Não foi possível formar o valor alvo\n"

int main(int argc, char *argv[]) {
    // Validate arguments count
    if(argc > 3){
        fprintf(stderr, TOO_MANY_ARGUMENTS_MESSAGE);
        return TOO_MANY_ARGUMENTS;
    }
    if(argc < 3){
        fprintf(stderr, TOO_FEW_ARGUMENTS_MESSAGE);
        return TOO_FEW_ARGUMENTS;
    }

    // Allocate inputs
    unsigned inputsLength = CountCharOfType(argv[1], ',') + 1;
    int inputs[inputsLength];
    
    // Get inputs
    if(!StringToIntArray(argv[1], inputs, inputsLength)){
        fprintf(stderr, INVALID_INPUT_MESSAGE);
        return INVALID_INPUT;
    }

    // Get target
    int target = atoi(argv[2]);
    
    // Handle case with only one input
    if (inputsLength == 1) {
        if(inputs[0] == target) {
            printf("(%d) = %d\n", inputs[0], target);
        } else {
            printf(NO_COMBINATION_FOUND_MESSAGE);
        }
        return 0;
    }
    
    // Number of operations in the equation
    unsigned inputsOperaionsLength = inputsLength - 1;
    
    // Create operations array
    Operation operations[] = {
        {Sum, '+'}, {Sub, '-'}, {Mul, '*'}, {Div, '/'}
    };
    unsigned operationsCount = sizeof(operations) / sizeof(operations[0]);
    unsigned operationIndex[inputsOperaionsLength];
    ResetUnsignedArray(operationIndex, inputsOperaionsLength);

    unsigned inputsPermutationsCount = Factorial(inputsLength);
    int *permutations[inputsPermutationsCount];
    FillPermutationsPointers(permutations, 0, inputsPermutationsCount);
    GetPermutations(inputs, inputsLength, permutations);

    Equation equation = {
        .inputs = inputs,
        .inputsLength = inputsLength,
        .inputsOperaionsLength = inputsOperaionsLength,
        .operations = operations,
        .operationsCount = operationsCount,
        .operationIndex = operationIndex
    };

    unsigned calls = 0;
    if(EquationTryFindTargetFromPermutations(&equation, target, &calls, permutations, inputsPermutationsCount)){
        PrintEquation(&equation);
        printf("\n");
        printf("%d\n", calls);
    } else {
        printf("%d\n", calls);
        printf(NO_COMBINATION_FOUND_MESSAGE);
    }
    
    return 0;
}