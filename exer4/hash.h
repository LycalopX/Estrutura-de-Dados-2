#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

#include "aluno.h"  // Struct Aluno definida para a hash

typedef struct node { // Struct para o nó
    Aluno novo;
    struct node* prox;
    int removido;  // 0 = ativo, 1 = removido
} Node;

typedef struct hash { // Struct para a tabela hash (junção dos nós)
    int tamanho;
    Node** tabela;
    char* caminho_arquivo;  // Novo campo para guardar o caminho
} HashT;

// Funções obrigatórias

HashT* criarHash(int tamanho,const char* caminhoArquivo); // Cria uma tabela hash

int inserirHash(HashT* h, Aluno aluno, const char* caminhoArquivo); // Insere aluno na tabela

Aluno* buscarHash(HashT* tabela, const char* nome); // Busca aluno pelo nome

int removerHash(HashT* tabela, const char* nome, const char* caminhoArquivo); // Remove Aluno da sua posição sem excluir o nó

void liberarHash(HashT* h); // Libera memória da tabela

// Funções auxiliares

int Hash(const char* nome, int tamanhoTabela); // Função hash usada na inserção, busca e remoção

unsigned int rotacionar13Bits(unsigned int valor); // Rotação de bits (auxiliar da hash)

void salvarHash(HashT* h, const char* caminhoArquivo); // Salva a tabela em arquivo

HashT* carregarHash(const char* caminhoArquivo); // Carrega tabela de arquivo

// Funções de depuração

void imprimirHash(HashT* h); // Imprime toda a tabela

#endif // HASH_H_INCLUDED
