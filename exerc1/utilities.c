#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utilities.h"

// Print
void PrintCharXTimesRecursive(char c, const unsigned times, unsigned currentIndex)
{
    if (currentIndex >= times)
    {
        return;
    }
    printf("%c", c);
    PrintCharXTimesRecursive(c, times, currentIndex + 1);
}

void PrintCharXTimes(char c, const unsigned times)
{
    PrintCharXTimesRecursive(c, times, 0);
}

// Input
unsigned CountCharOfTypeRecursive(char *str, char c, unsigned charactersLeft)
{
    if (charactersLeft == 0)
    {
        return 0;
    }

    return (str[0] == c) + CountCharOfTypeRecursive(str + 1, c, charactersLeft - 1);
}

unsigned CountCharOfType(char *str, char c)
{
    return CountCharOfTypeRecursive(str, c, strlen(str));
}

int StringToIntArrayRecursive(char *str, int *array, const unsigned size, unsigned index)
{
    if (index >= size)
    {
        return 1;
    }

    char *token = strtok(str, ",");
    if (token != NULL)
    {
        array[index] = atoi(token);
        return StringToIntArrayRecursive(str + strlen(token) + 1, array, size, index + 1);
    }
    return 0;
}

int StringToIntArray(char *str, int *array, const unsigned size)
{
    if (str == NULL || size == 0 || strlen(str) == 0 || array == NULL)
    {
        return 0;
    }

    return StringToIntArrayRecursive(str, array, size, 0);
}

// Permutation
int buffer[3628800][10];
void FillPermutationsPointers(int **permutations, int index, int total) {
    if (index >= total) return;

    permutations[index] = buffer[index];
    FillPermutationsPointers(permutations, index + 1, total);
}

void CopyArrayRecursive(int *dest, int *src, unsigned size, unsigned index)
{
    if (index >= size)
        return;
    dest[index] = src[index];
    CopyArrayRecursive(dest, src, size, index + 1);
}

void PermuteRecursive(
    int *array,
    unsigned size,
    int **permutations,
    int *current,
    unsigned *used,
    unsigned depth,
    unsigned *permIndex)
{
    if (depth == size)
    {
        CopyArrayRecursive(permutations[*permIndex], current, size, 0);
        (*permIndex)++;
        return;
    }

    PermuteIndexRecursive(array, size, permutations, current, used, depth, permIndex, 0);
}

void PermuteIndexRecursive(
    int *array,
    unsigned size,
    int **permutations,
    int *current,
    unsigned *used,
    unsigned depth,
    unsigned *permIndex,
    unsigned index)
{
    if (index >= size)
        return;

    if (!used[index])
    {
        used[index] = 1;
        current[depth] = array[index];
        PermuteRecursive(array, size, permutations, current, used, depth + 1, permIndex);
        used[index] = 0;
    }

    PermuteIndexRecursive(array, size, permutations, current, used, depth, permIndex, index + 1);
}

int GetPermutations(int *array, unsigned size, int **permutations)
{
    if (array == NULL || size == 0 || permutations == NULL)
        return 0;

    int current[size];
    unsigned used[size];
    unsigned permIndex = 0;

    ResetUnsignedArray(used, size);

    PermuteRecursive(array, size, permutations, current, used, 0, &permIndex);
    return 1;
}

unsigned Factorial(unsigned n)
{
    if (n == 0 || n == 1)
    {
        return 1;
    }
    return n * Factorial(n - 1);
}

// Reset array
void ResetIntArrayRecursive(int *array, const unsigned size, unsigned index)
{
    if (index >= size)
    {
        return;
    }

    array[index] = 0;
    ResetIntArrayRecursive(array, size, index + 1);
}

int ResetIntArray(int *array, const unsigned size)
{
    if (array == NULL || size == 0)
    {
        return 0;
    }

    ResetIntArrayRecursive(array, size, 0);
    return 1;
}

void ResetUnsignedArrayRecursive(unsigned *array, const unsigned size, unsigned index)
{
    if (index >= size)
    {
        return;
    }

    array[index] = 0;
    ResetUnsignedArrayRecursive(array, size, index + 1);
}

int ResetUnsignedArray(unsigned *array, const unsigned size)
{
    if (array == NULL || size == 0)
    {
        return 0;
    }
    ResetUnsignedArrayRecursive(array, size, 0);
    return 1;
}