#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readInputs.h"

void readInputs(int argc, char *argv[], char *algorithm, int *weights, int *count) {

    // Read algorithm
    strcpy(algorithm, argv[1]);

    // Read weights
    for (int i = 2; i < argc; i++) {
        weights[*count] = atoi(argv[i]);
        (*count)++;
    }
}
