#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

#include "aluno.h"  // Struct Aluno definida para a hash

typedef struct node { // Struct para o n�
    Aluno novo;
    struct node* prox;
    int removido;  // 0 = ativo, 1 = removido
} Node;

typedef struct hash { // Struct para a tabela hash (jun��o dos n�s)
    int tamanho;
    Node** tabela;
    char* caminho_arquivo;  // Novo campo para guardar o caminho
} HashT;

// Fun��es obrigat�rias

HashT* criarHash(int tamanho,const char* caminhoArquivo); // Cria uma tabela hash

int inserirHash(HashT* h, Aluno aluno, const char* caminhoArquivo); // Insere aluno na tabela

Aluno* buscarHash(HashT* tabela, const char* nome); // Busca aluno pelo nome

int removerHash(HashT* tabela, const char* nome, const char* caminhoArquivo); // Remove Aluno da sua posi��o sem excluir o n�

void liberarHash(HashT* h); // Libera mem�ria da tabela

// Fun��es auxiliares

int Hash(const char* nome, int tamanhoTabela); // Fun��o hash usada na inser��o, busca e remo��o

unsigned int rotacionar13Bits(unsigned int valor); // Rota��o de bits (auxiliar da hash)

void salvarHash(HashT* h, const char* caminhoArquivo); // Salva a tabela em arquivo

HashT* carregarHash(const char* caminhoArquivo); // Carrega tabela de arquivo

// Fun��es de depura��o

void imprimirHash(HashT* h); // Imprime toda a tabela

#endif // HASH_H_INCLUDED
