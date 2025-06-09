#include "reespalhamento.h"
#include "hashing.h"
#include "primo.h"

void overWriteFirstLine(int size, char *path) { /* ... implementation needed ... */ }

/**
 * @brief Finds the next available slot using quadratic probing on the Aluno array.
 */
int reespalhamentoQuadrático(Aluno *organizedData, int size, int place)
{
    int i = 1;
    while (1)
    {
        int busca = (place + i * i) % size;
        // Probe while the slot is occupied (state 0). Stop at empty or tombstone.
        if (organizedData[busca].state != 0)
        {
            return busca;
        }
        if (i > size)
        { // Failsafe
            fprintf(stderr, "Erro: tabela cheia, reespalhamento quadrático falhou.\n");
            return -1;
        }
        i++;
    }
}

/**
 * @brief Finds the next available slot using double hashing on the Aluno array.
 */
int reespalhamentoDuplo(Aluno *organizedData, int size, int place, int nUSP) 
{
    int i = 1;
    int h2 = 1 + (nUSP % (size - 1)); // CORRIGIDO: Usa o NUSP original

    while (1)
    {
        int busca = (place + i * h2) % size;
        if (organizedData[busca].state != 0)
        {
            return busca;
        }
        if (i > size)
        { // Failsafe
            fprintf(stderr, "Erro: tabela cheia, reespalhamento duplo falhou.\n");
            return -1;
        }
        i++;
    }
}

/**
 * @brief Rebuilds the hash table into a new, larger array of Aluno structs.
 */
void updateHashing(Aluno **organizedData, int oldSize, int newSize)
{
    Aluno *oldData = *organizedData;
    Aluno *newData = calloc(newSize, sizeof(Aluno));

    if (!newData)
    {
        fprintf(stderr, "Erro ao alocar memória para nova tabela hash.\n");
        return;
    }

    for (int i = 0; i < newSize; i++)
    {
        newData[i].state = 1; // Mark all new slots as empty.
    }

    // Re-hash every occupied slot from the old table into the new one.
    for (int i = 0; i < oldSize; i++)
    {
        if (oldData[i].state == 0)
        {
            int index = hashing(oldData[i].nUSP) % newSize;
            if (newData[index].state != 0)
            {
                newData[index] = oldData[i]; // Copy the entire struct.
            }
            else
            {
                int newIndex = reespalhamentoQuadrático(newData, newSize, index);
                if (newIndex != -1)
                    newData[newIndex] = oldData[i];
            }
        }
    }

    free(oldData);
    *organizedData = newData;
}

/**
 * @brief Decides which rehashing strategy to use based on the load factor.
 */
int reespalhamento(Aluno **organizedData, int *size, int previousHashing, double factor, int *newHash, char *pathFile, int nUSP)
{
    if (factor >= 0.9)
    {
        int oldSize = *size;
        *size = encontrarPrimo(*size);
        // overWriteFirstLine(*size, pathFile); // This function needs a proper implementation.
        updateHashing(organizedData, oldSize, *size);
        return reespalhamentoQuadrático(*organizedData, *size, hashing(previousHashing) % *size);
    }
    else if (factor >= 0.7)
    {
        if (!(*newHash))
        {
            *newHash = 1;
            updateHashing(organizedData, *size, *size); // Reorganize in place.
        }
        return reespalhamentoDuplo(*organizedData, *size, previousHashing, nUSP);
    }
    else
    {
        return reespalhamentoQuadrático(*organizedData, *size, previousHashing);
    }
}