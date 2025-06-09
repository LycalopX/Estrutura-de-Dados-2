#include <stdio.h>
#include <stdlib.h>

#include "hanoi.h"
#include "moveDisk.h"
#include "printArray.h"

void allocateDisks(struct pino **pinos, int count, int *weights)
{

    *pinos = malloc(3 * sizeof(struct pino));
    ; // alocar espaço para 3 pinos

    (*pinos)[0].discos = malloc(count * sizeof(struct peso)); // allocate each row
    (*pinos)[1].discos = malloc(count * sizeof(struct peso)); // allocate each row
    (*pinos)[2].discos = malloc(count * sizeof(struct peso)); // allocate each row

    (*pinos)[0].length = count;
    (*pinos)[1].length = 0;
    (*pinos)[2].length = 0;

    for (int i = 0; i < count; i++)
    {
        ((*pinos)[0].discos[i]).kg = weights[i];
        ((*pinos)[0].discos[i]).ordem = count - i;

        // Para eles que estão vazios, kg e ordem = -1.
        ((*pinos)[1].discos)[i].kg = -1;
        ((*pinos)[1].discos)[i].ordem = -1;

        ((*pinos)[2].discos)[i].kg = -1;
        ((*pinos)[2].discos)[i].ordem = -1;
    }
}

/*

Basicamente, para todo o conjunto de discos em um pino, é possível separar aquela pilha
no disco (n) da base, e em (n -1) discos que precisam ser movidos para um pino auxiliar,
os quais permitirão levar o conjunto ao destino final.

Seguindo essa recursão e usando structs para "fisicamente" mover os discos, é possível
rastrear de forma mais interessante o tamanho do peso movido.

*/

// Vamos aplicar?

void hanoi(struct pino *pinos, int n, char from, char to, char support, int *movedWeight, int *numberOfMoves)
{

    if (n == 1)
    {
        moveDisk(pinos, from, to, movedWeight);
        (*numberOfMoves)++;
        return;
    }

    hanoi(pinos, n - 1, from, support, to, movedWeight, numberOfMoves);
    moveDisk(pinos, from, to, movedWeight);

    hanoi(pinos, n - 1, support, to, from, movedWeight, numberOfMoves);
    (*numberOfMoves)++;
}

void setUp(int *weights, int count)
{
    struct pino *pinos;

    allocateDisks(&pinos, count, weights);

    int movedWeight = 0, numberOfMoves = 0;
    int ordemMaisAlta = pinos[0].discos[0].ordem;

    printf("\n");

    hanoi(pinos, ordemMaisAlta, 0, 2, 1, (&movedWeight), &numberOfMoves);

    printf("\n");

    printf("\nPeso movimentado: %du \nNúmero de movimentos: %d\n\n", movedWeight, numberOfMoves);

    // Limpar a memória alocada
    free(pinos[0].discos);
    free(pinos[1].discos);
    free(pinos[2].discos);
    free(pinos);
    pinos = NULL;
    weights = NULL;
}