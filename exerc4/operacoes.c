#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operacoes.h"
#include "hash.h"
#include "aluno.h"

/**
 * @brief Remove espaços em branco do início e do fim de uma string.
 * @param str A string a ser modificada.
 */
void trimWhitespace(char *str)
{
    if (str == NULL || *str == '\0')
        return;

    // Remove do início
    char *inicio = str;
    while (*inicio == ' ' || *inicio == '\t' || *inicio == '\n' || *inicio == '\r')
    {
        inicio++;
    }

    // Move o conteúdo para o início da string
    if (inicio != str)
    {
        memmove(str, inicio, strlen(inicio) + 1);
    }

    if (*str == '\0')
        return;

    // Remove do fim
    char *fim = str + strlen(str) - 1;
    while (fim >= str && (*fim == ' ' || *fim == '\t' || *fim == '\n' || *fim == '\r'))
    {
        *fim = '\0';
        fim--;
    }
}

/**
 * @brief Executa a operação de criação da tabela hash.
 * Cria uma tabela com o tamanho especificado e a salva em um arquivo vazio.
 */
void operacao_criar(const char *tamanho_str, const char *caminho)
{
    if (!tamanho_str || !caminho)
    {
        fprintf(stderr, "Uso: criar <tamanho> <caminho_arquivo>\n");
        return;
    }
    int tamanho = atoi(tamanho_str);
    if (tamanho <= 0)
    {
        fprintf(stderr, "Erro: O tamanho deve ser um numero positivo.\n");
        return;
    }

    // A função criarHash já salva um arquivo vazio inicial.
    HashT *tabela = criarHash(tamanho, caminho);
    if (tabela)
    {
        printf("Tabela criada com sucesso e salva em '%s'.\n", caminho);
        liberarHash(tabela);
    }
    else
    {
        fprintf(stderr, "Erro ao executar a operacao 'criar'.\n");
    }
}

/**
 * @brief Executa a operação de inserção de um ou mais alunos.
 * Carrega a tabela, insere os dados e salva as alterações.
 */
void operacao_inserir(const char *caminho, const char *dados)
{
    if (!caminho || !dados)
    {
        fprintf(stderr, "Uso: inserir <caminho_arquivo> \"<nome1:nusp1:curso1,...>\"\n");
        return;
    }

    HashT *tabela = carregarHash(caminho);
    if (!tabela)
    {
        // Se a tabela não pode ser carregada, talvez o arquivo não exista.
        // Criamos uma com tamanho padrão para prosseguir.
        // Supondo um tamanho padrão de 11, conforme o teste.
        tabela = criarHash(11, caminho);
        if (!tabela) {
             fprintf(stderr, "Erro: Nao foi possivel criar uma nova tabela para '%s'.\n", caminho);
             return;
        }
    }

    // Cria uma cópia dos dados para que strtok não modifique o argumento original.
    char *dados_copia = strdup(dados);
    if (!dados_copia)
    {
        fprintf(stderr, "Erro de alocacao de memoria.\n");
        liberarHash(tabela);
        return;
    }

    int count = 0;
    char *saveptr_aluno;
    char *aluno_str = strtok_r(dados_copia, ",", &saveptr_aluno);
    while (aluno_str != NULL)
    {
        trimWhitespace(aluno_str);
        
        char* saveptr_campo;
        char *nome = strtok_r(aluno_str, ":", &saveptr_campo);
        char *nusp_str = strtok_r(NULL, ":", &saveptr_campo);
        char *curso = strtok_r(NULL, "\0", &saveptr_campo);

        if (nome && nusp_str && curso)
        {
            trimWhitespace(nome);
            trimWhitespace(curso);
            
            Aluno a;
            a.nome = nome;
            a.nusp = atoi(nusp_str);
            a.curso = curso;

            if (inserirHash(tabela, a))
            {
                count++;
            }
        }
        aluno_str = strtok_r(NULL, ",", &saveptr_aluno);
    }

    free(dados_copia); // Libera a cópia

    if (count > 0)
    {
        salvarHash(tabela, caminho);
        printf("%d aluno(s) inserido(s) com sucesso. Tabela salva em '%s'.\n", count, caminho);
    }
    else
    {
        printf("Nenhum aluno valido para insercao foi fornecido ou ja existiam.\n");
    }

    liberarHash(tabela);
}

/**
 * @brief Executa a operação de busca de um ou mais alunos.
 * Carrega a tabela e imprime os dados dos alunos encontrados.
 */
void operacao_buscar(const char *caminho, const char *nomes)
{
    if (!caminho || !nomes)
    {
        fprintf(stderr, "Uso: buscar <caminho_arquivo> \"<nome1,nome2,...>\"\n");
        return;
    }

    HashT *tabela = carregarHash(caminho);
    if (!tabela)
    {
        fprintf(stderr, "Erro: Nao foi possivel carregar a tabela de '%s'.\n", caminho);
        return;
    }

    char *nomes_copia = strdup(nomes);
    if (!nomes_copia)
    {
        fprintf(stderr, "Erro de alocacao de memoria.\n");
        liberarHash(tabela);
        return;
    }

    printf("--- Resultado da Busca ---\n");
    char *saveptr;
    char *nome = strtok_r(nomes_copia, ",", &saveptr);
    while (nome != NULL)
    {
        trimWhitespace(nome);
        const Aluno *encontrado = buscarHash(tabela, nome);
        if (encontrado)
        {
            printf("Encontrado: %s:%d:%s\n", encontrado->nome, encontrado->nusp, encontrado->curso);
        }
        else
        {
            printf("Nao encontrado: '%s'\n", nome);
        }
        nome = strtok_r(NULL, ",", &saveptr);
    }

    free(nomes_copia);
    liberarHash(tabela);
}

/**
 * @brief Executa a operação de remoção de um ou mais alunos.
 * Carrega a tabela, remove os alunos e salva as alterações.
 */
void operacao_remover(const char *caminho, const char *nomes)
{
    if (!caminho || !nomes)
    {
        fprintf(stderr, "Uso: remover <caminho_arquivo> \"<nome1,nome2,...>\"\n");
        return;
    }

    HashT *tabela = carregarHash(caminho);
    if (!tabela)
    {
        fprintf(stderr, "Erro: Nao foi possivel carregar a tabela de '%s'.\n", caminho);
        return;
    }

    char *nomes_copia = strdup(nomes);
    if (!nomes_copia)
    {
        fprintf(stderr, "Erro de alocacao de memoria.\n");
        liberarHash(tabela);
        return;
    }

    int count = 0;
    char *saveptr;
    char *nome = strtok_r(nomes_copia, ",", &saveptr);
    while (nome != NULL)
    {
        trimWhitespace(nome);
        if (removerHash(tabela, nome))
        {
            printf("Removido: '%s'\n", nome);
            count++;
        }
        else
        {
            printf("Nao encontrado para remocao: '%s'\n", nome);
        }
        nome = strtok_r(NULL, ",", &saveptr);
    }

    free(nomes_copia);

    if (count > 0)
    {
        salvarHash(tabela, caminho);
        printf("%d aluno(s) removido(s) com sucesso. Tabela salva em '%s'.\n", count, caminho);
    }
    else
    {
        printf("Nenhum aluno foi removido.\n");
    }

    liberarHash(tabela);
}

/**
 * @brief Executa um conjunto de testes padrão para validar as funcionalidades do sistema.
 * Realiza operações de criação, inserção, remoção, salvamento e busca em sequência.
 */
void operacao_teste_padrao()
{
    const char *caminhoArquivo = "hash_nome.txt";

    // 1. Criar tabela hash
    printf("1. Criando tabela hash com tamanho 11...\n");
    HashT *tabela = criarHash(11, caminhoArquivo);
    if (!tabela)
    {
        fprintf(stderr, "Erro ao criar tabela hash.\n");
        return;
    }

    // 2. Inserir cinco alunos
    printf("\n2. Inserindo 5 alunos...\n");
    Aluno alunosInserir[] = {
        {"Joao", 1234567, "Engenharia"},
        {"Maria", 7654321, "Medicina"},
        {"Carlos", 9876543, "Direito"},
        {"Ana", 1928374, "Arquitetura"},
        {"Pedro", 9182736, "Administracao"}};
    for (int i = 0; i < 5; i++)
    {
        if(!inserirHash(tabela, alunosInserir[i])) {
            printf("Falha ao inserir %s\n", alunosInserir[i].nome);
        }
    }
    printf("Tentativa de insercao de 5 alunos em memoria.\n");

    // 3. Remover dois deles
    printf("\n3. Removendo 2 alunos (Joao e Ana)...\n");
    removerHash(tabela, "Joao");
    removerHash(tabela, "Ana");
    printf("2 alunos removidos da memoria.\n");

    // 4. Salvar a tabela no arquivo
    printf("\n4. Salvando a tabela final em '%s'...\n", caminhoArquivo);
    salvarHash(tabela, caminhoArquivo);
    printf("Tabela salva.\n");
    liberarHash(tabela);
    tabela = NULL;

    // 5. Carregar do arquivo e buscar
    printf("\n5. Carregando a tabela do arquivo e realizando buscas...\n");
    tabela = carregarHash(caminhoArquivo);
    if (!tabela)
    {
        fprintf(stderr, "Erro ao carregar a tabela do arquivo para o teste de busca.\n");
        return;
    }

    const char *alunosBuscar[] = {"Maria", "Pedro", "Tiago"}; // 
    for (int i = 0; i < 3; i++)
    {
        printf("Buscando por '%s': ", alunosBuscar[i]);
        const Aluno *encontrado = buscarHash(tabela, alunosBuscar[i]);
        if (encontrado)
        {
            printf("Encontrado -> %s:%d:%s\n", encontrado->nome, encontrado->nusp, encontrado->curso);
        }
        else
        {
            printf("Nao encontrado.\n");
        }
    }

    printf("\nTeste padrao concluido.\n");
    liberarHash(tabela);
}