#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "moveDisk.h"

static inline void swapDisk(struct peso *disk1, struct peso *disk2)
{

    // Armazenar o valor do vetor a ser trocado
    struct peso temp = *disk1;

    // Trocar os discos de lugar
    *disk1 = *disk2;
    *disk2 = temp;
}

// Troca o disco de posição, indica o pino que foi movido, reduz o tamanho (length), aumenta a sequência
// Reseta pino que tinha sido movido na etapa anterior

void moveDisk(struct pino *pinos, int n1, int n2, int *movedWeight)
{
    struct pino *orig = &(pinos[n1]);
    struct pino *dest = &(pinos[n2]);

    if (orig->length == 0)
        return; /* nada para mover          */

    int from = orig->length - 1; /* topo da origem           */
    int to = dest->length;       /* próxima posição destino  */

    // Definir peso sendo movido
    int weightOrigin = orig->discos[from].kg;

    // Informar movimento
    printf("Disco %d kg: Pino %d -> Pino %d\n", weightOrigin, n1 + 1, n2 + 1);

    // Aumentar contagem de peso movido
    (*movedWeight) = (*movedWeight) + weightOrigin;

    /* --- troca efetiva --- */

    swapDisk(&(orig->discos[from]), &(dest->discos[to]));

    orig->length--; /* pop da origem            */
    dest->length++; /* push no destino          */
}
