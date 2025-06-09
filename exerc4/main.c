#include <stdio.h>
#include <string.h>

// Incluímos apenas a nossa interface de operações.
// O main não precisa mais saber sobre hash.h ou aluno.h.
#include "operacoes.h"

// O main agora apenas interpreta os argumentos da linha de comando
// e chama a função de operação correspondente.
int main(int argc, char *argv[]) {
    
    // Se nenhum argumento for passado, executa o teste padrão.
    if (argc < 2) {
        operacao_teste_padrao();
        return 0;
    }

    char *comando = argv[1];

    if (strcmp(comando, "criar") == 0) {
        // Ex: programa.exe criar 11 hash.txt
        if (argc != 4) {
            fprintf(stderr, "Uso: %s criar <tamanho> <caminho_arquivo>\n", argv[0]);
            return 1;
        }
        operacao_criar(argv[2], argv[3]);

    } else if (strcmp(comando, "inserir") == 0) {
        // Ex: programa.exe inserir hash.txt "Aluno1:1:CC,Aluno2:2:EC"
        if (argc != 4) {
            fprintf(stderr, "Uso: %s inserir <caminho_arquivo> \"<dados>\"\n", argv[0]);
            return 1;
        }
        operacao_inserir(argv[2], argv[3]);

    } else if (strcmp(comando, "buscar") == 0) {
        // Ex: programa.exe buscar hash.txt "Aluno1,Aluno3"
        if (argc != 4) {
            fprintf(stderr, "Uso: %s buscar <caminho_arquivo> \"<nomes>\"\n", argv[0]);
            return 1;
        }
        operacao_buscar(argv[2], argv[3]);

    } else if (strcmp(comando, "remover") == 0) {
        // Ex: programa.exe remover hash.txt "Aluno2,Aluno4"
        if (argc != 4) {
            fprintf(stderr, "Uso: %s remover <caminho_arquivo> \"<nomes>\"\n", argv[0]);
            return 1;
        }
        operacao_remover(argv[2], argv[3]);
    
    } else {
        fprintf(stderr, "Comando desconhecido: '%s'\n", comando);
        fprintf(stderr, "Comandos disponiveis: criar, inserir, buscar, remover\n");
        return 1;
    }

    return 0;
}