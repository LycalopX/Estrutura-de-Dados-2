#include "readHashing.h"

// Serve para transmitir dados do arquivo para array de modificação
void readHashing(char ***organizedData, char *pathFile, int *size, int *takenSpace)
{

    FILE *fptr = fopen(pathFile, "r");

    if (fptr == NULL)
    {
        printf("Erro ao abrir o arquivo em %s\n", pathFile);
        return; // Erro ao abrir o arquivo
    }

    char buffer[256]; // ou até 512, se quiser mais folga

    // Reads and skips a line
    if (!fgets(buffer, sizeof(buffer), fptr))
    {
        fclose(fptr);
        return;
    }

    (*size) = atoi(buffer);

    *organizedData = calloc(*size, sizeof(char *));

    if (!*organizedData)
    {
        perror("calloc");
        fclose(fptr);
        return;
    }

    for (int i = 0; i < (*size); i++)
    {
        if (fgets(buffer, sizeof(buffer), fptr))
        {
            (*organizedData)[i] = malloc(256);
            if (!(*organizedData)[i])
            {
                perror("malloc");
                continue;
            }
            strcpy((*organizedData)[i], buffer);
            (*takenSpace)++;

            // remove newline final se houver
            size_t len = strlen((*organizedData)[i]);
            if (len > 0 && (*organizedData)[i][len - 1] == '\n')
            {
                (*organizedData)[i][len - 1] = '\0';
                (*takenSpace)--;
            }
        }
    }

    fclose(fptr);
};