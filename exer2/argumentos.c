#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "argumentos.h"

void make_vector(int **vet, int *tam_vet, char *token) {
    if(token != NULL) {
        // Alocar mais espaço no vetor para o novo elemento
        *vet = realloc(*vet, (*tam_vet + 1) * sizeof(int));
        // Converter o token para inteiro e armazenar no vetor
        (*vet)[*tam_vet] = atoi(token);
        // Incrementar o tamanho do vetor
        (*tam_vet)++;
        // Obter o próximo token
        token = strtok(NULL, ",");
        // Chamada recursiva para processar o próximo token
        make_vector(vet, tam_vet, token);
    }
}

void tratar_argumentos(char *arg1, char *arg3, int **vet, int *tam_vet, int **valores, int *tam_valores) {
    char *token;
    // Processar o primeiro argumento (vetor)
    *tam_vet = 0; // Inicializar o tamanho do vetor
    token = strtok(arg1, ",");
    *vet = NULL;
    make_vector(vet, tam_vet, token);

    // Processar o segundo argumento (valores)
    *tam_valores = 0; // Inicializar o tamanho do vetor de valores
    token = strtok(arg3, ",");
    *valores = NULL;
    make_vector(valores, tam_valores, token);
}