#include "inserir.h"
#include "hashing.h"
#include "reespalhamento.h"
#include "readHashing.h"
#include "aluno.h" // Use the Aluno struct

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Inserts new students into the hash table.
 */
int inserir(char *path, char *data)
{
    char pathFile[64];
    snprintf(pathFile, sizeof(pathFile), "./%s.txt", path);

    Aluno *organizedData;
    int size, takenSpace = 0;

    readHashing(&organizedData, pathFile, &size, &takenSpace);

    char *token = strtok(data, ",");
    int i, newHash = 0;
    double factor;

    while (token)
    {
        factor = ((double)(takenSpace)) / ((double)(size));

        char *nUSP_str = token;
        char *nome = strtok(NULL, ",");
        char *curso = strtok(NULL, ",");

        if (!nome || !curso)
            break;

        int nUSP = atoi(nUSP_str);
        int hashIndex = hashing(nUSP) % size;
        i = hashIndex;

        if (organizedData[i].state == 0 || (factor >= 0.9))
        {
            i = reespalhamento(&organizedData, &size, i, factor, &newHash, pathFile, nUSP);
        }
        
        // Populate the struct fields with the new student's data.
        organizedData[i].nUSP = nUSP;
        strncpy(organizedData[i].nome, nome, sizeof(organizedData[i].nome) - 1);
        organizedData[i].nome[sizeof(organizedData[i].nome) - 1] = '\0';
        strncpy(organizedData[i].curso, curso, sizeof(organizedData[i].curso) - 1);
        organizedData[i].curso[sizeof(organizedData[i].curso) - 1] = '\0';
        organizedData[i].state = 0; // Mark as occupied.

        token = strtok(NULL, ",");
        takenSpace++;
    }

    // Rewrite the file with updated data from the struct array.
    FILE *fptr = fopen(pathFile, "w");
    fprintf(fptr, "%d\n", size);
    for (int j = 0; j < size; j++)
    {
        if (organizedData[j].state == 0) // Occupied
            fprintf(fptr, "%d;%s;%s\n", organizedData[j].nUSP, organizedData[j].nome, organizedData[j].curso);
        else if (organizedData[j].state == 2) // Tombstone
            fprintf(fptr, "+\n");
        else // Empty
            fprintf(fptr, "\n");
    }
    fclose(fptr);

    // Free the single block of memory for the array.
    free(organizedData);

    printf("Dados inseridos em %s.\n\n", pathFile);
    return 0;
}