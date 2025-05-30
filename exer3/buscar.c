#include "buscar.h"
#include "hashing.h"
#include "inserir.h"
#include "readHashing.h"

int buscarHash(int nUSP, char **organizedData, int size)
{
    int hash = hashing(nUSP);
    int i = hash;

    int nusp;
    sscanf(organizedData[hash], "%d;", &nusp);

    if (nusp != nUSP)
    {
        while (i < size)
        {
            sscanf(organizedData[i], "%d;", &nusp);
            if (nUSP == nusp)
            {
                break;
            }
            i++;
        }
        if (size == i)
        {
            printf("Aluno NUSP %d não foi encontrado.\n", nUSP);
            return -1;
        }
    }

    return i;
};

void buscar(int argc, char **argv)
{
    char *path = argv[2];
    char *nUSPs = argv[3];

    char *token = strtok(nUSPs, ",");

    char pathFile[64], **organizedData;
    int size, takenSpace = 0, nUSP, index;
    // 15 + tamanho atual é o tamanho máximo do nome do arquivo

    snprintf(pathFile, sizeof(pathFile), "../%s.txt", path); // Salvando na pasta storage.

    readHashing(&organizedData, pathFile, &size, &takenSpace);

    while (token)
    {
        nUSP = atoi(token);

        index = buscarHash(nUSP, organizedData, size);

        if (index > 0)
        {
            printf("%s\n", organizedData[index]);
        }

        token = strtok(NULL, ","); // Próximo número USP
    }

    printf("Procura terminada.\n\n");
}