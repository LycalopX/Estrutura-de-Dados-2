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

void moveDisk(struct pino *orig, struct pino *dest, int prevDest, int heaviest)
{
    if (orig->length == 0) return;             /* nada para mover          */

    int from = orig->length - 1;               /* topo da origem           */
    int to   = dest->length;                   /* próxima posição destino  */

    /* --- ajuste de streak na origem --- */
    if (orig->length >= 2) {
        
        int under = orig->discos[from-1].ordem;
        if (orig->discos[from].ordem == under + 1 && (heaviest >= under))
            orig->streak--;
    }

    /* --- troca efetiva --- */

    swapDisk(&(orig->discos[from]), &(dest->discos[to]));

    /* --- ajuste de streak no destino --- */
    if (dest->length >= 1) {                   /* havia pelo menos 1 disco */

        int under = dest->discos[to-1].ordem;
        if (dest->discos[to].ordem == under + 1 && heaviest >= under)
            dest->streak++;
    }

    orig->length--;                            /* pop da origem            */
    dest->length++;                            /* push no destino          */
}
