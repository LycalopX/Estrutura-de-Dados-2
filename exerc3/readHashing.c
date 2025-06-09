#include "readHashing.h"

// Lê os dados da tabela hash do arquivo e armazena em memória
void readHashing(char ***organizedData, char *pathFile, int *size, int *takenSpace)
{
    FILE *fptr = fopen(pathFile, "r");

    if (fptr == NULL)
    {
        printf("Erro ao abrir o arquivo em %s\n", pathFile);
        return;
    }

    char buffer[256];

    // Lê a primeira linha: tamanho da tabela
    if (!fgets(buffer, sizeof(buffer), fptr))
    {
        fclose(fptr);
        return;
    }

    (*size) = atoi(buffer);

    // Aloca array de ponteiros para armazenar os dados da tabela
    *organizedData = calloc(*size, sizeof(char *));
    if (!*organizedData)
    {
        perror("calloc");
        fclose(fptr);
        return;
    }

    // Lê cada linha do arquivo e armazena no array
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

            // Remove o '\n' do final, se houver (linha vazia não conta como ocupada)
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
