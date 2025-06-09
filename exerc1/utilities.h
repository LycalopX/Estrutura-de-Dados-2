#ifndef __UTILITIES_H__
#define __UTILITIES_H__

// Prints a character X times
void PrintCharXTimes(char c, const unsigned times);

// Counts the number of times a character appears in a string
unsigned CountCharOfType(char* str, char c);
// Converts a string of integers separated by commas into an array of integers
// Returns 1 if successful, 0 otherwise
int StringToIntArray(char* str, int* array, const unsigned size);

// Converts an array of integers into an array of arrays of integers, where each sub-array is a permutation of the original array
// Returns 1 if successful, 0 otherwise
int GetPermutations(int *array, unsigned size, int **permutations);
// Recursive function to use a buffer for permutations
void FillPermutationsPointers(int **permutations, int index, int total);
// Copies an array recursively
void CopyArrayRecursive(int *dest, int *src, unsigned size, unsigned index);
// Recursive function to permute an array of integers
void PermuteIndexRecursive(
    int *array,
    unsigned size,
    int **permutations,
    int *current,
    unsigned *used,
    unsigned depth,
    unsigned *permIndex,
    unsigned index);
// Calculates the factorial of a number
unsigned Factorial(unsigned n);

// Resets an array of integers to 0
int ResetIntArray(int* array, unsigned size);
// Resets an array of unsigned integers to 0
int ResetUnsignedArray(unsigned* array, unsigned size);

#endif