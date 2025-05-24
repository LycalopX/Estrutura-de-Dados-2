// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Functions
#include "heap.h"
#include "printArray.h"
#include "quicksort.h"
#include "swap.h"
#include "solve.h"

// Main function
int main()
{
    char algorithm[5], line[1024];
    int weights[100], count = 0;

    // Ler inputs
    if (fgets(line, sizeof(line), stdin))
    {

        // Ler a linha de entrada
        char *ptr = line;

        if (sscanf(ptr, "%s", algorithm) == 1)
        {
            // Ignorar a palavra chave (algoritmo)
            ptr = strchr(ptr, ' ');
            if (ptr)
                ptr++;

            while (sscanf(ptr, "%d", &weights[count]) == 1)
            {
                count++;

                // Mover o ponteiro adiante
                while (*ptr && *ptr != ' ')
                    ptr++;
                if (*ptr == ' ')
                    ptr++;
            }
        }
    }

    // Caso você quer heap ou sort.
    if (!strcmp(algorithm, "heap"))
    {
        heapSort(weights, count);
    }
    else if (!strcmp(algorithm, "quick"))
    {
        quicksort(weights, 0, count - 1);
    }
    else
    {
        heapSort(weights, count);
    }

    // Conjunto de discos
    struct peso *discos = (struct peso *) malloc(sizeof(struct peso) * count);

    // Para colocar cada elemento na struct
    for (int i = 0; i < count; i++)
    {
        discos[i].kg = weights[i];
        discos[i].ordem = i;
    }

    solve(discos, count);

    return 0;
}