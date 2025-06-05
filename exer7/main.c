#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "solver.h"

int main(int argc, char *argv[]) {
    if(argc == 2){
        int n = atoi(argv[1]);
        if (n <= 0 || n>14) {
            printf("Valor inválido para N. Deve ser entre 1 e 14 (para nao estourar memoria).\n");
            return 1;
        }
        inicializar(n);
    }
    else{
        printf("Executando testes padronizados\n\n");

        // Teste 1
        int n = 4;
        printf("Teste N = %d\n", n);
        inicializar(n);

        printf("\n");

        // Teste 2
        n = 8;
        printf("Teste N = %d\n", n);
        inicializar(n);
    }
    return 0;
}