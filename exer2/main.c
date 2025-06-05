#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "busca.h"
#include "print.h"
#include "argumentos.h"


int main(int argc, char *argv[]) {
    if(argc == 1){
        printf("Executando testes padronizados\n\n");
        // Teste 1
        int vet1[] = {8, 8, 6, 5, 5, 5, 3, 2, 1};
        int tam_vet1 = sizeof(vet1)/sizeof(vet1[0]);
        int valores1[] = {5, 8, 7};
        int tam_valores1 = sizeof(valores1)/sizeof(valores1[0]);
        int ordem1 = 2; // 2 para decrescente
        int *intervalo1 = (int*)malloc(tam_valores1*sizeof(int));

        printf("Resultado do primeiro teste:\n");
        buscar_intervalos(vet1, ordem1, valores1, tam_vet1, tam_valores1, intervalo1, 0);
        printar_intervalos(intervalo1, tam_valores1, 0);
        free(intervalo1);

        // Teste 2
        int vet2[] = {1, 2, 3, 3, 3, 4, 5, 6};
        int tam_vet2 = sizeof(vet2)/sizeof(vet2[0]);
        int valores2[] = {3, 7};
        int tam_valores2 = sizeof(valores2)/sizeof(valores2[0]);
        int ordem2 = 1; // 1 para crescente
        int *intervalo2 = (int*)malloc(tam_valores2*sizeof(int));

        printf("\n");
        printf("Resultado do segundo teste:\n");
        buscar_intervalos(vet2, ordem2, valores2, tam_vet2, tam_valores2, intervalo2, 0);
        printar_intervalos(intervalo2, tam_valores2, 0);
        free(intervalo2);
    }
    else if (argc == 4){
        int ordem;
        int *vet = NULL, *valores = NULL, *intervalo = NULL;
        int tam_vet, tam_valores;
        if(strcmp(argv[2], "asc") == 0){
            ordem = 1; // Crescente
        }
        else if(strcmp(argv[2], "desc") == 0){
            ordem = 2; // Decrescente
        }

        tratar_argumentos(argv[1], argv[3], &vet, &tam_vet, &valores, &tam_valores);
        if(vet == NULL || valores == NULL) {
            printf("Erro ao processar os argumentos.\n");
            return 1;
        }

        intervalo = (int*)malloc(tam_valores * sizeof(int));

        buscar_intervalos(vet, ordem, valores, tam_vet, tam_valores, intervalo, 0);
        printar_intervalos(intervalo, tam_valores, 0);

        free(vet);
        free(valores);
        free(intervalo);
    }
    return 0;
}