#include "buscar.h"
#include "hashing.h"
#include "inserir.h"
#include "readHashing.h"

// Busca linear a partir da posição de hash até encontrar o nUSP ou fim do array
int buscarHash(int nUSP, char **organizedData, int size)
{
    int hash = hashing(nUSP) % size;
    int nusp;

    for (int i = hash; i < size; i++)
    {
        sscanf(organizedData[i], "%d;", &nusp);
        if (nusp == nUSP)
        {
            return i; // Encontrado
        }
    }

    printf("Aluno NUSP %d não foi encontrado.\n", nUSP);
    return -1; // Não encontrado
}

// Função principal da busca, chamada pela main
void buscar(int argc, char **argv)
{
    char *path = argv[2];
    char *nUSPs = argv[3];
    char *token = strtok(nUSPs, ",");

    char pathFile[64], **organizedData;
    int size, takenSpace = 0, nUSP, index;

    snprintf(pathFile, sizeof(pathFile), "../%s.txt", path); // Define o caminho do arquivo

    readHashing(&organizedData, pathFile, &size, &takenSpace); // Lê dados do arquivo para memória

    // Processa cada NUSP fornecido na linha de comando
    while (token)
    {
        nUSP = atoi(token);
        index = buscarHash(nUSP, organizedData, size);

        if (index >= 0)
        {
            printf("%s\n", organizedData[index]); // Exibe dados do aluno encontrado
        }

        token = strtok(NULL, ","); // Próximo NUSP
    }

    printf("Procura terminada.\n\n");
}
