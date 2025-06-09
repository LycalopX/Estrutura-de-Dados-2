#include <stdio.h>
#include <stdlib.h>
#include "busca.h"

int busca_binaria(int *vetor, int ordem, int pos, int valor, int esq, int dir){
    //"pos" define se a busca é para o início (0) ou fim (1) do intervalo

    if(esq > dir){ // Retorna -1 se o valor não for encontrado
        return -1;
    }
    int meio = (dir+esq)/2;

    if((vetor[meio] < valor && ordem == 1) || (vetor[meio] > valor && ordem == 2)){ //Se não encontrou o valor, continua a busca pela direita, de acordo com a ordenação
        return busca_binaria(vetor, ordem, pos, valor, meio+1, dir);
    }
    else if((vetor[meio] > valor && ordem == 1) || (vetor[meio] < valor && ordem == 2)){ //Se não encontrou o valor, continua a busca pela esquerda, de acordo com a ordenação
        return busca_binaria(vetor, ordem, pos, valor, esq, meio-1);
    }
    else if(vetor[meio] == valor){
        if(pos == 0){
            int inicio = busca_binaria(vetor, ordem, pos, valor, esq, meio-1); // Continua a busca pela esquerda para encontrar o início do intervalo
            // Se encontrou o início, retorna o índice; caso contrário, retorna o "meio"
            if(inicio != -1){
                return inicio;
            }
            else {
                return meio;
            }
        }
        else if(pos == 1){
            int fim = busca_binaria(vetor, ordem, pos, valor, meio+1, dir); // Continua a busca pela direita para encontrar o fim do intervalo
            // Se encontrou o fim, retorna o índice; caso contrário, retorna o "meio"
            if(fim != -1){
                return fim;
            }
            else {
                return meio;
            }
        }
    }

    return -1;
}

int buscar_intervalos(int *vetor, int ordem, int *valores, int tam_vet, int tam_valores, int *intervalo, int i){
    if(i >= tam_valores){ // Para a recursão quando todos os valores foram processados
        return 0;
    }
    int inicio = busca_binaria(vetor, ordem, 0, valores[i], 0, tam_vet-1); // Busca o início do intervalo para o valor[i]
    int fim = busca_binaria(vetor, ordem, 1, valores[i], 0, tam_vet-1); // Busca o fim do intervalo para o valor[i]
    intervalo[i * 2] = inicio;
    intervalo[i * 2 + 1] = fim;

    buscar_intervalos(vetor, ordem, valores, tam_vet, tam_valores, intervalo, i + 1); // Chama recursivamente para o próximo valor
    return 0;
}


