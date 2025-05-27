// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Functions
#include "heap.h"
#include "printArray.h"
#include "quicksort.h"
#include "swap.h"
#include "hanoi.h"
#include "readInputs.h"

// Main function
int main(int argc, char *argv[])
{
    char *algorithm = malloc(5 * sizeof(char));
    int *weights = malloc(100 * sizeof(int)), count = 0;

    readInputs(argc, argv, algorithm, weights, &count);

    // Caso você quer heap ou sort.
    if (!strcmp(algorithm, "heap"))
    {
        heapSort(weights, count);
        printf("\nAlgoritmo usado: HeapSort\n\n");
    }
    else if (!strcmp(algorithm, "quick"))
    {
        quicksort(weights, 0, count - 1);
        printf("\nAlgoritmo usado: QuickSort\n\n");
    }

    setUp(weights, count);

    free(weights);
    free(algorithm);
    weights = NULL;
    algorithm = NULL;
    // Limpar a memória alocada

    return 0;
}