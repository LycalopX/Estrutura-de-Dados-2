#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readInputs.h"


void readInputs(char *algorithm, int *weights, int *count) {

    char line[1024];

    // Ler inputs
    if (fgets(line, sizeof(line), stdin))
    {

        // Ler a linha de entrada
        char *ptr = line;

        // Vamos tentar ler a primeira palavra como um número
        int temp;

        if (sscanf(ptr, "%d", &temp) != 1)
        {
            sscanf(ptr, "%s", algorithm);

            // Ignorar a palavra chave (algoritmo)
            ptr = strchr(ptr, ' ');
            if (ptr)
                ptr++;
        }


            while (sscanf(ptr, "%d", &weights[*count]) == 1)
            {
                (*count)++;

                // Mover o ponteiro adiante
                while (*ptr && *ptr != ' ')
                    ptr++;
                if (*ptr == ' ')
                    ptr++;
            }
    }
}
