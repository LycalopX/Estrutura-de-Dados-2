#include "inserir.h"
#include "hashing.h"
#include "reespalhamento.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int inserir(char *path, char *data)
{

    FILE *fptr;
    char pathFile[64];
    // 15 + tamanho atual é o tamanho máximo do nome do arquivo

    snprintf(pathFile, sizeof(pathFile), "../storage/%s.txt", path); // Salvando na pasta storage.

    fptr = fopen(pathFile, "a+"); // Abrindo o arquivo para escrita no final

    if (fptr == NULL)
    {
        printf("Erro ao abrir o arquivo em %s\n", pathFile);
        return -1; // Erro ao abrir o arquivo
    }

    /* volta ao início para poder ler o primeiro inteiro */
    rewind(fptr); // ou fseek(fptr, 0, SEEK_SET);

    // Obter tamanho da Hashing
    int size;

    if (fscanf(fptr, "%d", &size) != 1)
    {
        fprintf(stderr, "Não foi possível ler o tamanho da hashing em %s\n", pathFile);
        fclose(fptr);
        return -1;
    }

    /* volta ao fim para continuar gravando */
    fseek(fptr, 0, SEEK_END);

    char **organizedData = calloc(size, sizeof(char *));
    if (!organizedData)
    {
        perror("calloc");
        fclose(fptr);
        return -1;
    }

    // Inserindo informação no arquivo
    char *token = strtok(data, ",");
    int i, takenSpace = 0, newHash = 0;

    while (token)
    {
        char *nUSP = token;
        char *nome = strtok(NULL, ",");
        char *curso = strtok(NULL, ",");

        i = hashing(atoi(nUSP)) % size;

        if (!nome || !curso)
            break;

        // Inserir aluno por aluno na Hashing

        if (organizedData[i])
        {
            i = reespalhamento(&organizedData, &size, i, takenSpace, &newHash, pathFile, &fptr);
            // Do stuff to mirror here
        }

        organizedData[i] = malloc(sizeof(char) * 256);
        if (!organizedData[i])
        {
            perror("malloc"); /* libere tudo e retorne */
        }

        snprintf(organizedData[i], 256, "%s;%s;%s", nUSP, nome, curso);

        printf("Olha q pintão %s com Hashing %d\n", organizedData[i]);

        token = strtok(NULL, ","); // Próximo número USP
        takenSpace++;
    }

    // Colocar no arquivo e em suas determinadas posições (cada valor hashing)
    for (int i = 0; i < size; i++)
    {

        if (organizedData[i])
        {
            fprintf(fptr, "%s\n", organizedData[i]);

            printf("Posição %d na Hashing \n%s\n", i, organizedData[i]);
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

    return 0; // Sucesso
}