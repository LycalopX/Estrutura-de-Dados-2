#include <stdio.h>

#include "equation.h"
#include "utilities.h"

// Print
void PrintEquationRecursive(const Equation *equation, unsigned currentIndex) {
    if(currentIndex > equation->inputsOperaionsLength) {
        return;
    }

    printf("%c %d) ", equation->operations[equation->operationIndex[currentIndex - 1]].operationChar, equation->inputs[currentIndex]);
    PrintEquationRecursive(equation, currentIndex + 1);
}

void PrintEquation(const Equation *equation) {
    PrintCharXTimes('(', equation->inputsOperaionsLength);
    printf("%d ", equation->inputs[0]);
    PrintEquationRecursive(equation, 1);
    int state = 1;
    int value = EquationValue(equation, &state);
    if(state){
        printf("= %d", value);
    }
    else{
        printf("= Error");
    }
}

// Value
int EquationValueRecursive(const Equation *equation, unsigned currentIndex, int currentValue, int *state) {
    if(currentIndex >= equation->inputsLength) {
        return currentValue;
    }

    int newValue = UseOperation(currentValue, equation->inputs[currentIndex], state, &equation->operations[equation->operationIndex[currentIndex - 1]]);
    return EquationValueRecursive(equation, currentIndex + 1, newValue, state);
}

int EquationValue(const Equation *equation, int *state) {
    return EquationValueRecursive(equation, 1, equation->inputs[0], state);
}

// Next combination
int NextCombinationRecursive(const Equation *equation, unsigned currentIndexAdd1) {
    // Whould be index -1
    if (currentIndexAdd1 == 0) {
        return 0;
    }
    
    equation->operationIndex[currentIndexAdd1 - 1]++;

    if(equation->operationIndex[currentIndexAdd1 - 1] > equation->operationsCount - 1) {
        equation->operationIndex[currentIndexAdd1 - 1] = 0;
        return NextCombinationRecursive(equation, currentIndexAdd1 - 1);
    }

    return 1;
}

int NextCombination(const Equation *equation) {
    int newCombination = NextCombinationRecursive(equation, equation->inputsOperaionsLength);
    return newCombination;
}

// Try find target
int EquationTryFindTargetRecursive(const Equation *equation, int target, int *state, unsigned *calls) {
    (*calls)++;
    int value = EquationValue(equation, state);

    if (value == target && *state) {
        return 1;
    }
    else if(NextCombination(equation)){
        return EquationTryFindTargetRecursive(equation, target, state, calls);
    }

    return 0;
}

int EquationTryFindTarget(const Equation *equation, int target, unsigned *calls) {
    int state = 1;
    return EquationTryFindTargetRecursive(equation, target, &state, calls);
}