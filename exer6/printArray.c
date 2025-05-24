#include "printArray.h"
#include <stdio.h>

void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void printPino(struct pino x)
{
    int i = 0;

    printf("Tamanho: %d \n", x.length);

    printf("Discos: \n");

    while (i < x.length)
    {
        printf("%d ", x.discos[i].kg);
        i++;
    }

    printf("\n");
}
