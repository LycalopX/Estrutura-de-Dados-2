#ifndef OPERACOES_H_INCLUDED
#define OPERACOES_H_INCLUDED

#include "hash.h" // Incluímos hash.h porque as operações manipulam a tabela

/**
 * @brief Executa um conjunto de testes padrão para validar as funcionalidades do sistema.
 */
void operacao_teste_padrao();

/**
 * @brief Executa a operação de criação da tabela hash.
 */
void operacao_criar(const char* tamanho_str, const char* caminho);

/**
 * @brief Executa a operação de inserção de um ou mais alunos.
 */
void operacao_inserir(const char* caminho, const char* dados);

/**
 * @brief Executa a operação de busca de um ou mais alunos.
 */
void operacao_buscar(const char* caminho, const char* nomes);

/**
 * @brief Executa a operação de remoção de um ou mais alunos.
 */
void operacao_remover(const char* caminho, const char* nomes);


#endif // OPERACOES_H_INCLUDED