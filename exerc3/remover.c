#include "remover.h"
#include "buscar.h"
#include "readHashing.h"
#include "aluno.h" // Use the Aluno struct

/**
 * @brief Updates the data file from the modified Aluno struct array.
 */
void updateFile(Aluno *organizedData, int size, char *path)
{
    FILE *fptr = fopen(path, "w");
    if (!fptr)
    {
        perror("Erro ao abrir arquivo para escrita");
        return;
    }

    fprintf(fptr, "%d\n", size); // Write the table size.

    // Write each entry to the file based on its state.
    for (int i = 0; i < size; i++)
    {
        if (organizedData[i].state == 0) // Occupied
            fprintf(fptr, "%d;%s;%s\n", organizedData[i].nUSP, organizedData[i].nome, organizedData[i].curso);
        else if (organizedData[i].state == 2) // Tombstone
            fprintf(fptr, "+\n");
        else // Empty
            fprintf(fptr, "\n");
    }
    fclose(fptr);
}

/**
 * @brief Removes students by marking their entries as tombstones.
 */
void remover(int argc, char **argv)
{
    char *path = argv[2];
    char *nUSPs = argv[3];
    char *token = strtok(nUSPs, ",");

    char pathFile[64];
    Aluno *organizedData;
    int size, takenSpace = 0;

    snprintf(pathFile, sizeof(pathFile), "./%s.txt", path);
    readHashing(&organizedData, pathFile, &size, &takenSpace);

    while (token)
    {
        int nUSP = atoi(token);
        // Passa o takenSpace para a função de busca
        int index = buscarHash(nUSP, organizedData, size, takenSpace);

        if (index >= 0)
        {
            printf("Aluno NUSP %d removido\n", nUSP);
            // Mark the slot with a tombstone instead of freeing memory.
            organizedData[index].state = 2;
        }

        token = strtok(NULL, ",");
    }

    // Save the modified table back to the file.
    updateFile(organizedData, size, pathFile);
    free(organizedData);

    printf("Usuários solicitados removidos.\n\n");
}