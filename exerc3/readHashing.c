#include "readHashing.h"
#include "aluno.h"

void readHashing(Aluno **organizedData, char *pathFile, int *size, int *takenSpace)
{
    FILE *fptr = fopen(pathFile, "r");
    if (fptr == NULL)
    {
        printf("Erro ao abrir o arquivo em %s\n", pathFile);
        return;
    }

    char buffer[256];
    if (!fgets(buffer, sizeof(buffer), fptr))
    {
        fclose(fptr);
        return;
    }

    *size = atoi(buffer);
    *takenSpace = 0;

    // Allocate memory for an array of Aluno structs
    *organizedData = calloc(*size, sizeof(Aluno));
    if (!*organizedData)
    {
        perror("calloc failed");
        fclose(fptr);
        return;
    }

    // Read each line and parse it into the corresponding struct.
    for (int i = 0; i < *size; i++)
    {
        if (!fgets(buffer, sizeof(buffer), fptr))
        {
            // If file ends prematurely, mark remaining slots as empty.
            (*organizedData)[i].state = 1;
            continue;
        }

        // Remove newline character for safe comparison.
        buffer[strcspn(buffer, "\n")] = 0;

        if (buffer[0] == '\0')
        {
            (*organizedData)[i].state = 1; // 1 = Empty
        }
        else if (strcmp(buffer, "+") == 0)
        {
            (*organizedData)[i].state = 2; // 2 = Tombstone
        }
        else
        {
            // Parse the data line directly into the struct fields.
            sscanf(buffer, "%d;%127[^;];%63[^\n]",
                   &(*organizedData)[i].nUSP,
                   (*organizedData)[i].nome,
                   (*organizedData)[i].curso);
            (*organizedData)[i].state = 0; // 0 = Occupied
            (*takenSpace)++;
        }
    }

    fclose(fptr);
}