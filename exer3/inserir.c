#include "inserir.h"
#include "hashing.h"
#include "reespalhamento.h"
#include "readHashing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Checa se uma string está contida no começo de outra (útil para rapidamente verificar nUSP)
int prefix(const char *pre, const char *str)
{
    return strncmp(pre, str, strlen(pre)) == 0;
}

int inserir(char *path, char *data)
{

    // Abrindo arquivo usando path indicado
    FILE *fptr;
    char pathFile[64];

    snprintf(pathFile, sizeof(pathFile), "../%s.txt", path);

    // Array onde memória do arquivo será armazenada para alterações
    char **organizedData;
    int size, takenSpace = 0;

    // Obter informações (se presentes) prévias da hashing
    readHashing(&organizedData, pathFile, &size, &takenSpace);

    // Inserindo nova informação no arquivo
    char *token = strtok(data, ",");
    int i, newHash = 0;

    // Fator de carga
    double factor = ((double)(takenSpace)) / ((double)(size));

    while (token)
    {

        factor = ((double)(takenSpace)) / ((double)(size));
        char *nUSP = token;
        char *nome = strtok(NULL, ",");
        char *curso = strtok(NULL, ",");

        i = hashing(atoi(nUSP)) % size;

        if (!nome || !curso)
            break;

            // Colisão / Fc >= 0.9
        if (organizedData[i] || (factor >= 0.9))
        {
            // Entrada duplicada
            if (prefix(nUSP, organizedData[i]))
            {

                // Entrada Repetida
                token = strtok(NULL, ","); // Próximo número USP
                continue;
            }

            i = reespalhamento(&organizedData, &size, i, factor, &newHash, pathFile);
            // Do stuff to mirror here
        }

        organizedData[i] = malloc(sizeof(char) * 256);
        if (!organizedData[i])
        {
            perror("malloc"); /* libere tudo e retorne */
        }

        snprintf(organizedData[i], 256, "%s;%s;%s", nUSP, nome, curso);

        token = strtok(NULL, ","); // Próximo número USP
        takenSpace++;
    }

    fptr = fopen(pathFile, "w"); // Atualizar arquivo
    fprintf(fptr, "%d\n", size);

    // Colocar no arquivo e em suas determinadas posições (cada valor hashing)
    for (int i = 0; i < size; i++)
    {
        if (organizedData[i])
        {
            fprintf(fptr, "%s\n", organizedData[i]);
        }
        else
        {
            fprintf(fptr, "\n");
        }
    }

    // Liberar a memória
    fclose(fptr);

    for (int i = 0; i < size; ++i)
    {
        if (organizedData[i])
            free(organizedData[i]);
    }
    free(organizedData);

    printf("Dados inseridos em %s.\n\n", pathFile); // Operação concluída

    return 0; // Sucesso
}