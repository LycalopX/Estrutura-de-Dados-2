#include "criar.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void criar(int size, char *path)
{
    char pathFile[64]; 
    // 15 + tamanho atual é o tamanho máximo do nome do arquivo
    FILE *fptr;

    // Create a file
    snprintf(pathFile, sizeof(pathFile), "../storage/%s.txt", path); // Salvando na pasta storage.

    fptr = fopen(pathFile, "w"); // Abrindo o arquivo para escrita

    if (fptr == NULL)
    {
        printf("Erro ao criar o arquivo em %s\n", pathFile);
        return;
    }

    fprintf(fptr, "%d\n", size); // Informando o tamanho da tabela hash na primeira linha

    fclose(fptr);
    printf("Tabela hash criada com sucesso em %s\n", pathFile);
}