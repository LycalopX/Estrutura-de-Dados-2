// Arquivo: buscar.c

#include "buscar.h"
#include "hashing.h"
#include "readHashing.h"
#include "aluno.h"

/**
 * @brief Procura por um aluno usando a estratégia de sondagem correta (quadrática ou dupla) 
 * baseada no fator de carga da tabela.
 * @param nUSP O Número USP a ser procurado.
 * @param organizedData O array da tabela hash.
 * @param size O tamanho da tabela.
 * @param takenSpace O número de slots ocupados.
 * @return O índice do aluno se encontrado, ou -1 se não encontrado.
 */
int buscarHash(int nUSP, Aluno *organizedData, int size, int takenSpace)
{
    double factor = ((double)takenSpace) / size;
    int hash = hashing(nUSP) % size;
    int i = 0;

    // Percorre a tabela usando a estratégia de sondagem apropriada
    while (i < size)
    {
        int currentIndex;

        if (factor < 0.7)
        {
            // Usa sondagem quadrática
            currentIndex = (hash + i * i) % size;
        }
        else
        {
            // Usa reespalhamento duplo (usando a chave nUSP original)
            int h2 = 1 + (nUSP % (size - 1));
            currentIndex = (hash + i * h2) % size;
        }

        // Condição 1: Encontrou o aluno
        if (organizedData[currentIndex].state == 0 && organizedData[currentIndex].nUSP == nUSP)
        {
            return currentIndex; // Sucesso!
        }

        // Condição 2: Encontrou um espaço nunca utilizado (fim da linha de sondagem)
        if (organizedData[currentIndex].state == 1)
        {
            break; 
        }

        // Se for um "tombstone" (state == 2), o loop continua a busca.
        i++;
    }
    
    // Se o loop terminar sem encontrar o aluno, imprime a mensagem aqui.
    printf("Aluno NUSP %d não foi encontrado.\n", nUSP);
    return -1;
}

void buscar(int argc, char **argv)
{
    char *path = argv[2];
    char *nUSPs = argv[3];
    char *token = strtok(nUSPs, ",");

    char pathFile[64];
    Aluno *organizedData;
    int size, takenSpace = 0;

    snprintf(pathFile, sizeof(pathFile), "./%s.txt", path);
    readHashing(&organizedData, pathFile, &size, &takenSpace);

    while (token)
    {
        int nUSP = atoi(token);
        // ATUALIZADO: Passa o 'takenSpace' para a função de busca
        int index = buscarHash(nUSP, organizedData, size, takenSpace);

        if (index >= 0)
        {
            printf("%d;%s;%s\n", organizedData[index].nUSP, organizedData[index].nome, organizedData[index].curso);
        }

        token = strtok(NULL, ",");
    }

    free(organizedData);
    printf("Procura terminada.\n\n");
}