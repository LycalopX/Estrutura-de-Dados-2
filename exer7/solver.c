#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "solver.h"

int chamadas = 0;
int totalSolucoes = 0;
typedef struct
{
    int pos[15]; // Armazena a posição das rainhas na solução
} Solucao;

Solucao solucoes[50000]; // Alocando espaço para armazenar até 50.000 soluções (n = 14) para evitar estouro de memória

void rotacionar90(int *dest, int *orig, int n)
{ // Rotaciona a matriz 90 graus no sentido horário
    for (int i = 0; i < n; i++)
    {
        dest[n - 1 - orig[i]] = i;
    }
    return;
}

void refletir(int *dest, int *orig, int n)
{ // Reflete a matriz horizontalmente
    for (int i = 0; i < n; i++)
    {
        dest[n - 1 - i] = orig[i];
    }
    return;
}

int igual(int *a, int *b, int n)
{ // Verifica se os dois vetores são iguais
    for (int i = 0; i < n; i++)
    {
        if (a[i] != b[i])
        {
            return 0;
        }
    }
    return 1;
}

int verificar_solucao(int *rainhas, int n)
{ // Para verificar as equivalencias basta verificar as rotações (0°, 90°, 180°, 270°) e fazer uma reflexão de cada
    int temp[n], rot[n], ref[n];
    memcpy(temp, rainhas, n * sizeof(int));
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < totalSolucoes; j++)
        {
            if (igual(temp, solucoes[j].pos, n))
                return 0; // Já existe uma solução equivalente
        }
        refletir(ref, temp, n);
        for (int j = 0; j < totalSolucoes; j++)
        {
            if (igual(ref, solucoes[j].pos, n))
                return 0; // Já existe uma solução equivalente
        }
        rotacionar90(rot, temp, n);
        memcpy(temp, rot, n * sizeof(int));
    }

    // Salva a nova solução encontrada
    memcpy(solucoes[totalSolucoes].pos, rainhas, n * sizeof(int));
    totalSolucoes++;

    // Printa a solução encontrada
    printf("Solução %d: [", totalSolucoes);
    for (int i = 0; i < n; i++)
    {
        printf("%d", rainhas[i]);
        if (i != n - 1)
            printf(", ");
    }
    printf("]\n");

    return 1;
}

int resolver(int n, int col, int *rainhas, int *linUsada, int *diag1Usada, int *diag2Usada)
{
    chamadas++;

    if (col == n)
    { // Solução encontrada
        verificar_solucao(rainhas, n);
        return 1;
    }

    for (int lin = 0; lin < n; lin++)
    {
        if (linUsada[lin] == 0 && diag1Usada[lin - col + n] == 0 && diag2Usada[lin + col] == 0)
        { // Se a linha e as diagonais não estão ocupadas
            // Coloca a rainha e marca as linhas e diagonais como ocupadas
            rainhas[col] = lin;
            linUsada[lin] = 1;
            diag1Usada[lin - col + n] = 1;
            diag2Usada[lin + col] = 1;
            resolver(n, col + 1, rainhas, linUsada, diag1Usada, diag2Usada); // Chamada recursiva para a próxima coluna

            // Volta para o estado anterior (backtracking)
            rainhas[col] = 0;
            linUsada[lin] = 0;
            diag1Usada[lin - col + n] = 0;
            diag2Usada[lin + col] = 0;
        }
    }
    return 0;
}

void inicializar(int n)
{
    int rainhas[n];
    int linUsada[n];
    int diag1Usada[2 * n];
    int diag2Usada[2 * n];
    memset(linUsada, 0, sizeof(int) * n);
    memset(diag1Usada, 0, sizeof(int) * (2 * n));
    memset(diag2Usada, 0, sizeof(int) * (2 * n));
    chamadas = 0;
    totalSolucoes = 0;
    resolver(n, 0, rainhas, linUsada, diag1Usada, diag2Usada);

    if (totalSolucoes == 0)
    {
        printf("Nao ha solucao para %d rainhas.\n", n);
    }
    else
    {
        printf("Total de chamadas recursivas: %d\n", chamadas);
        printf("Total de soluções para N = %d: %d\n", n, totalSolucoes);
    }
}