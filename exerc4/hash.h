#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

#include "aluno.h"  // Struct Aluno definida para a hash

typedef struct node { // Struct para o nó
    Aluno novo;
    struct node* prox;
} Node;

typedef struct hash { // Struct para a tabela hash
    int tamanho;
    Node** tabela;
} HashT;

// --- Funções Principais ---

// Cria uma tabela hash com o tamanho mais próximo a um número primo.
HashT* criarHash(int tamanho,const char* caminhoArquivo); 

// Insere um aluno na tabela.
int inserirHash(HashT* h, Aluno aluno); 

// Busca um aluno pelo nome e retorna um ponteiro constante para ele.
const Aluno* buscarHash(HashT* tabela, const char* nome);

// Remove um aluno da tabela pelo nome.
int removerHash(HashT* tabela, const char* nome); 

// Libera toda a memória alocada para a tabela hash.
void liberarHash(HashT* h); 

// --- Funções Auxiliares ---

// Calcula o índice hash para um dado nome.
int funcaoHash(const char* nome, int tamanhoTabela); 

// Salva o conteúdo da tabela hash em um arquivo.
void salvarHash(HashT* h, const char* caminhoArquivo); 

// Carrega uma tabela hash a partir de um arquivo.
HashT* carregarHash(const char* caminhoArquivo); 

#endif // HASH_H_INCLUDED