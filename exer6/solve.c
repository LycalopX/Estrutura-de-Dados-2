#include <stdio.h>
#include <stdlib.h>

#include "solve.h"
#include "moveDisk.h"

void printPino(struct pino x)
{
    int i = 0;

    printf("Streak: %d \n", x.streak);
    printf("Tamanho: %d \n", x.length);

    printf("Discos: \n");

    while (i < x.length)
    {
        printf("%d ", x.discos[i].kg);
        i++;
    }

    printf("\n");
}

void inicializePinos(int count, struct pino *pino1, struct pino *pino2, struct pino *pino3)
{
    for (int i = 0; i < count; i++)
    {
        (*pino1).discos[i].ordem = (count - i);

        // Para eles que estão vazios, kg e ordem = -1.
        (*pino2).discos[i].kg = -1;
        (*pino2).discos[i].ordem = -1;

        (*pino3).discos[i].kg = -1;
        (*pino3).discos[i].ordem = -1;
    }

    pino1->streak = pino2->streak = pino3->streak = 0;

    pino1->length = count;
    pino2->length = pino3->length = 0;
}

/*

Em ordem de prioridades.

Básico: Não é possível mover pino maior para cima de um pino menor

    1.
    Não deve ser possível movimentar o elemento do pino para qual foi movimentado da última vez
    (passado como argumento na recursão)

    2.
    Sempre moveremos o maior peso disponível quando houver uma array vazia, exceto se essa array
    for a primeira.

    3.
    Sempre registrar o peso de maior ordem movimentado (quando movido)

    4.
    Se um peso de ordem n - 1 for retirado de cima de um disco cujo peso for maior que o de maior ordem
movimentado até então, isso não contará para a streak daquele pino.

    6.
    A streak servirá como previsão do próximo movimento mais otimizado.

    Sequências com pesos pares:
    Terão seu pino removido e inserido no lado oposto da array de maior sequência.

    Sequências com pesos ímpares:
    Terão seu pino removido e inserido na array de maior sequência.

    7.
    Em um impasse, a sequência com o pino mais leve tem o elemento movimentado e segue a regra 6.


*/

// Vamos aplicar?
void move(struct pino *pinos, int prevMoved, int heaviest, int *pesoMovimentado)
{
    int origin;
    int dest;

    // Analisar comparativamente os pinos, um por um
    for (int p1 = 0; p1 < 3; p1++)
    {
        int p2 = (p1 + 1) % 3;
        int p3 = (p1 + 2) % 3;

        int p1l = (pinos)[p1].length - 1;
        int p2l = (pinos)[p2].length - 1;
        int p3l = (pinos)[p3].length - 1;

        if (p2l < 0)
        {
            p2l = 0;
        }
        if (p3l < 0)
        {
            p3l = 0;
        }

        struct peso w1, w2, w3;

        w1 = (pinos)[p1].discos[p1l];
        w2 = (pinos)[p2].discos[p2l];
        w3 = (pinos)[p3].discos[p3l];

        // Regra 1
        if (p1 == prevMoved)
        {
            continue;
        }

        //  Regra 2
        if ((pinos)[p2].length == 0 && p2 != 0)
        {
            // Mover o maior peso disponível

            if (w1.kg > w3.kg)
            {
                origin = p1;
            }
            else
            {
                origin = p3;
            }
            dest = p2;
            prevMoved = p2;

            break;
        }
        else if ((pinos)[p3].length == 0 && p3 != 0)
        {
            // Mover o maior peso disponível

            if (w1.kg > w2.kg)
            {
                origin = p1;
            }
            else
            {
                origin = p2;
            }
            dest = p3;
            prevMoved = p3;

            break;
        }

        // Movimentado anteriormente
        struct peso w0 = (pinos)[prevMoved].discos[(pinos)[prevMoved].length - 1];

        int isSmallest = (w1.kg < w2.kg || w2.kg < 0) && (w1.kg < w3.kg || w3.kg < 0);
        int isMiddle = ((w1.kg < w2.kg || w2.kg < 0) && (w1.kg > w3.kg)) || ((w1.kg > w2.kg) && (w1.kg < w3.kg || w3.kg < 0));

        // Derivado da Regra básica: se o peso 1 for o mais leve, e o peso de segunda menor ordem
        // é o bloqueado de movimento, o peso 1 é o único que pode ser movido
        if (isSmallest && (w0.ordem < w3.ordem && w0.ordem > w1.ordem))
        {

            origin = p1;
            dest = prevMoved;

            break;
        }

        if (isMiddle) {
            
        }

        // Em caso de empate
        if (isSmallest)
        {
            origin = p1;

            if ((w1.kg - w2.kg) < (w1.kg - w3.kg))
            {
                dest = p2;
            }
            else
            {
                dest = p3;
            }
        }
    }

    struct peso worigin = (pinos)[origin].discos[(pinos)[origin].length - 1];

    if (pinos[dest].length == 0)
    {
        printf("Movendo peso %d para pino vazio #%d \n", worigin.kg, dest + 1);
    }
    else
    {
        struct peso wdest = (pinos)[dest].discos[(pinos)[dest].length - 1];
        printf("Trocando peso %d com peso %d \n", worigin.kg, wdest.kg);
    }

    moveDisk(pinos, origin, dest, prevMoved, heaviest);

    // Aumentar contagem de pesos movimentados
    (*pesoMovimentado) += worigin.kg;

    /* Caso o pino movimentado seja o maior movimentado até agora (apenas a ordem importa,
    para manter sequência)... (Regra 3) */
    if (worigin.ordem > heaviest)
    {
        heaviest = worigin.ordem;
    }

    // Caso todos os pesos do pino 1 foram movidos, e não reste pesos em outros pinos
    if ((pinos)[0].length == 0 && ((pinos)[1].length == 0 || (pinos)[2].length == 0))
    {
        return;
    }

    // Se não, continuar recursivamente...
    move(pinos, prevMoved, heaviest, pesoMovimentado);
}

void solve(struct peso *vector, int count)
{
    struct pino *pinos = (struct pino *)malloc(sizeof(struct pino) * 3);

    int prevMoved = -1, heaviest = 1, pesoMovimentado;

    // Inicializa os pinos
    pinos[0].discos = vector;
    pinos[1].discos = (struct peso *)malloc(sizeof(struct peso) * (count));
    pinos[2].discos = (struct peso *)malloc(sizeof(struct peso) * (count));

    inicializePinos(count, &(pinos[0]), &(pinos[1]), &(pinos[2]));

    printf("----------------------------------------------\n            Configuração inicial: \n----------------------------------------------");

    printf("\nPino 1 \n");
    printPino((pinos[0]));
    printf("\nPino 2 \n");
    printPino((pinos[1]));
    printf("\nPino 3 \n");
    printPino((pinos[2]));

    printf("\n");

    move(pinos, 3, 1, &pesoMovimentado);

    printf("\n");

    printf("----------------------------------------------\n            Configuração final: \n----------------------------------------------");

    printf("\nPino 1 \n");
    printPino((pinos[0]));
    printf("\nPino 2 \n");
    printPino((pinos[1]));
    printf("\nPino 3 \n");
    printPino((pinos[2]));

    printf("\n\n Peso movimentado: %d", pesoMovimentado);
}