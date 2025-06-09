#include <stdio.h>
#include <stdlib.h>
#include "print.h"

int printar_intervalos(int *intervalo, int tam_valores, int i){
    if(i >= tam_valores){ // Para a recursão quando todos os valores foram processados
        return 0;
    }
    if(i==0){
        printf("Intervalos encontrados para cada valor:\n");
    }

    // Para evitar imprimir vírgula no último intervalo
    if(i>=0 && i<tam_valores-1){
        printf("(%d, %d), ", intervalo[i * 2], intervalo[i * 2 + 1]);
    }
    else if(i == tam_valores - 1){
        printf("(%d, %d)\n", intervalo[i * 2], intervalo[i * 2 + 1]);
    }

    // Chamada recursiva para o próximo intervalo
    printar_intervalos(intervalo, tam_valores, i + 1);
    
    return 0;
}