#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utilities.h"

// Print
void PrintCharXTimesRecursive(char c, const unsigned times, unsigned currentIndex) {
    if(currentIndex >= times) {
        return;
    }
    printf("%c", c);
    PrintCharXTimesRecursive(c, times, currentIndex + 1);
}

void PrintCharXTimes(char c, const unsigned times) {
    PrintCharXTimesRecursive(c, times, 0);
}

// Input
unsigned CountCharOfTypeRecursive(char* str, char c, unsigned charactersLeft){
    if(charactersLeft == 0) {
        return 0;
    }

    return (str[0] == c) + CountCharOfTypeRecursive(str + 1, c, charactersLeft - 1);
}

unsigned CountCharOfType(char* str, char c){
    return CountCharOfTypeRecursive(str, c, strlen(str));
}

int StringToIntArrayRecursive(char* str, int* array, const unsigned size, unsigned index) {
    if (index >= size) {
        return 1;
    }

    char* token = strtok(str, ",");
    if (token != NULL) {
        array[index] = atoi(token);
        return StringToIntArrayRecursive(str + strlen(token) + 1, array, size, index + 1);
    }
    return 0;
}

int StringToIntArray(char* str, int *array, const unsigned size) {  
    if(str == NULL || size == 0 || strlen(str) == 0 || array == NULL) {
        return 0;
    }
    
    return StringToIntArrayRecursive(str, array, size, 0);
}

// Reset array
void ResetIntArrayRecursive(int* array, const unsigned size, unsigned index) {
    if(index >= size) {
        return;
    }

    array[index] = 0;
    ResetIntArrayRecursive(array, size, index + 1);
}

int ResetIntArray(int* array, const unsigned size) {
    if(array == NULL || size == 0) {
        return 0;
    }

    ResetIntArrayRecursive(array, size, 0);
    return 1;
}

void ResetUnsignedArrayRecursive(unsigned* array, const unsigned size, unsigned index) {
    if(index >= size) {
        return;
    }
    
    array[index] = 0;
    ResetUnsignedArrayRecursive(array, size, index + 1);
}

int ResetUnsignedArray(unsigned* array, const unsigned size) {
    if(array == NULL || size == 0) {
        return 0;
    }
    ResetUnsignedArrayRecursive(array, size, 0);
    return 1;
}