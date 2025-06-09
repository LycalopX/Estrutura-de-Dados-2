#include "criar.h"
#include "primo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Cria arquivo de tabela hash com tamanho informado
void criar(int size, char *path)
{
    char pathFile[64];
    FILE *fptr;

    // Monta o caminho completo para o arquivo .txt
    snprintf(pathFile, sizeof(pathFile), "./%s.txt", path);

    fptr = fopen(pathFile, "w"); // Abre para escrita (cria novo arquivo)

    if (fptr == NULL)
    {
        printf("Erro ao criar o arquivo em %s\n", pathFile);
        return;
    }

    // Escreve o tamanho da tabela na primeira linha do arquivo
    fprintf(fptr, "%d\n", encontrarPrimo(size));

    fclose(fptr);
    printf("Tabela hash criada com sucesso em %s\n\n", pathFile);
}
