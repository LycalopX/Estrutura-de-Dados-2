#include "quicksort.h"
#include "swap.h"
#include <stdio.h>

int partition(int *vector, int min, int max) {

    // Nós escolhemos o último (em contraste ao primeiro)
    int pivot = vector[max];

    // Começa a varrer por baixo
    int i = min - 1;


    for (int j = min; j < max; j++) {

        // Caso o valor do elemento sendo analisado é maior que o pivot,
        // i (que representa o número de elementos à esquerda do 40)
        // definirá a posição final do pivot

        // Além disso, o número maior é jogado para trás, e o menor para frente
        // com a função definida em swap.h "swap".

        if (vector[j] > pivot) {
            i++;

            swap(&vector[i], &vector[j]);
        }   
    }


    swap(&vector[i+1], &vector[max]);
    return (i + 1);

}

void quicksort(int *vector, int min, int max) {
    // Repete-se o processo de particionar, até apenas restar uma
    // array de tamanho 0 (min == max)

    if (min < max) {
        int index = partition(vector, min, max);

        // Repete-se
        
        // De baixo para index
        quicksort(vector, min, index - 1);
        // De index para cima
        quicksort(vector, index + 1, max);
    }
}

