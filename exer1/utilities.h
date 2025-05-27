#ifndef __UTILITIES_H__
#define __UTILITIES_H__

// Prints a character X times
void PrintCharXTimes(char c, const unsigned times);

// Counts the number of times a character appears in a string
unsigned CountCharOfType(char* str, char c);
// Converts a string of integers separated by commas into an array of integers
// Returns 1 if successful, 0 otherwise
int StringToIntArray(char* str, int* array, const unsigned size);

// Resets an array of integers to 0
int ResetIntArray(int* array, unsigned size);
// Resets an array of unsigned integers to 0
int ResetUnsignedArray(unsigned* array, unsigned size);

#endif