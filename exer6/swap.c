#include "swap.h"
#include <stdio.h>

int swap(int *i, int *j) {
    // Armazenar o valor do vetor a ser trocado
    int temp = * i; 

    // Trocar os valores
    *i = *j;
    *j = temp;
    return 0; 
}