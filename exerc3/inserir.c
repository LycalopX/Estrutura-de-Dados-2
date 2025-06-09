#include "inserir.h"
#include "hashing.h"
#include "reespalhamento.h"
#include "readHashing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Verifica se 'pre' é prefixo de 'str'
int prefix(const char *pre, const char *str)
{
    return strncmp(pre, str, strlen(pre)) == 0;
}

// Insere alunos na tabela hash a partir de uma string de dados
int inserir(char *path, char *data)
{
    FILE *fptr;
    char pathFile[64];
    snprintf(pathFile, sizeof(pathFile), "../%s.txt", path); // Caminho completo do arquivo

    char **organizedData;
    int size, takenSpace = 0;

    // Lê tabela hash atual do arquivo
    readHashing(&organizedData, pathFile, &size, &takenSpace);

    char *token = strtok(data, ",");
    int i, newHash = 0;
    double factor = ((double)(takenSpace)) / ((double)(size)); // Fator de carga inicial

    // Processa entradas em pares de 3: nUSP, nome, curso
    while (token)
    {
        factor = ((double)(takenSpace)) / ((double)(size));

        char *nUSP = token;
        char *nome = strtok(NULL, ",");
        char *curso = strtok(NULL, ",");

        int hashIndex = hashing(atoi(nUSP)) % size;
        i = hashIndex;

        if (!nome || !curso)
            break;

        // Se posição está ocupada ou fator de carga está alto, reespalhar
        if (organizedData[i] != NULL || (factor >= 0.9))
        {
            if (organizedData[i][0] != '+') // Ignora lápides
            {
                i = reespalhamento(&organizedData, &size, i, factor, &newHash, pathFile);
            }
        }

        // Armazena o novo aluno no índice calculado
        organizedData[i] = malloc(sizeof(char) * 256);
        if (!organizedData[i])
        {
            perror("malloc");
        }

        snprintf(organizedData[i], 256, "%s;%s;%s", nUSP, nome, curso);

        token = strtok(NULL, ",");
        takenSpace++;
    }

    // Regrava o arquivo com os dados atualizados
    fptr = fopen(pathFile, "w");
    fprintf(fptr, "%d\n", size);

    for (int i = 0; i < size; i++)
    {
        if (organizedData[i])
            fprintf(fptr, "%s\n", organizedData[i]);
        else
            fprintf(fptr, "\n");
    }

    // Libera memória usada
    fclose(fptr);

    for (int i = 0; i < size; ++i)
    {
        if (organizedData[i])
            free(organizedData[i]);
    }
    free(organizedData);

    printf("Dados inseridos em %s.\n\n", pathFile);
    return 0;
}
