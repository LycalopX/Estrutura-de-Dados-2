#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "aluno.h"

// Rotaciona os bits de um valor unsigned int 13 posições para a esquerda.
unsigned int rotacionar13Bits(unsigned int valor)
{
    const int BITS_INT = 32; // Assumindo int de 32 bits
    return (valor << 13) | (valor >> (BITS_INT - 13));
}

// Calcula o índice hash para uma string (nome do aluno).
int funcaoHash(const char *nome, int tamanhoTabela)
{
    if (nome == NULL || tamanhoTabela <= 0)
    {
        return -1;
    }

    unsigned int h1 = 0;
    for (int i = 0; nome[i] != '\0'; i++)
    {
        h1 += (unsigned char)nome[i] << (i % 8);
    }

    h1 = rotacionar13Bits(h1);

    return h1 % tamanhoTabela;
}

// Salva o conteúdo da tabela hash em um arquivo de texto.
void salvarHash(HashT *h, const char *caminho)
{
    FILE *arquivo = fopen(caminho, "w");
    if (!arquivo)
    {
        fprintf(stderr, "Erro: Nao foi possivel abrir o arquivo '%s' para escrita.\n", caminho);
        return;
    }

    for (int i = 0; i < h->tamanho; i++)
    {
        fprintf(arquivo, "%d:", i);
        Node *atual = h->tabela[i];
        if (atual != NULL)
        {
            fprintf(arquivo, " "); // Adiciona um espaço após o ':' se houver nós
        }
        while (atual != NULL)
        {
            fprintf(arquivo, "%s:%d:%s", atual->novo.nome, atual->novo.nusp, atual->novo.curso);
            atual = atual->prox;
            if (atual != NULL)
            {
                fprintf(arquivo, ", ");
            }
        }
        fprintf(arquivo, "\n");
    }
    fclose(arquivo);
}

// Carrega uma tabela hash a partir de um arquivo, preservando a ordem dos nós.
HashT *carregarHash(const char *caminhoArquivo)
{
    FILE *arquivo = fopen(caminhoArquivo, "r");
    if (!arquivo)
    {
        // Silencioso se o arquivo não existir, pois pode ser criado depois.
        return NULL;
    }

    // Passada 1: Determinar o tamanho da tabela pelo maior índice no arquivo.
    int max_indice = -1;
    char linha_teste[1024];
    while (fgets(linha_teste, sizeof(linha_teste), arquivo))
    {
        int indice_atual;
        if (sscanf(linha_teste, "%d:", &indice_atual) == 1)
        {
            if (indice_atual > max_indice)
            {
                max_indice = indice_atual;
            }
        }
    }

    int tamanho_tabela = (max_indice > -1) ? max_indice + 1 : 10;
    rewind(arquivo);

    // Passada 2: Alocar e preencher a tabela.
    HashT *tabela = (HashT *)malloc(sizeof(HashT));
    if (!tabela)
    {
        fclose(arquivo);
        return NULL;
    }
    tabela->tamanho = tamanho_tabela;
    tabela->tabela = (Node **)calloc(tamanho_tabela, sizeof(Node *));

    if (!tabela->tabela)
    {
        free(tabela);
        fclose(arquivo);
        return NULL;
    }

    char linha[1024];
    while (fgets(linha, sizeof(linha), arquivo))
    {
        char *linha_ptr = linha;
        char *separador_indice = strchr(linha_ptr, ':');
        if (!separador_indice)
            continue;

        *separador_indice = '\0';
        int indice = atoi(linha_ptr);

        if (indice < 0 || indice >= tamanho_tabela)
            continue;

        char *alunos_str = separador_indice + 1;
        // Pula espaços em branco após o ':'
        while (*alunos_str == ' ')
            alunos_str++;

        char *saveptr_aluno;
        char *aluno_tok = strtok_r(alunos_str, ",", &saveptr_aluno);

        Node *cauda = NULL;

        while (aluno_tok != NULL)
        {
            char *saveptr_campo;
            char *nome = strtok_r(aluno_tok, ":", &saveptr_campo);
            char *nusp_str = strtok_r(NULL, ":", &saveptr_campo);
            char *curso_tok = strtok_r(NULL, "\n\r", &saveptr_campo); // Captura o resto da string do aluno

            // Remove espaços em branco do início/fim do curso se houver
            if (curso_tok)
            {
                char *end = curso_tok + strlen(curso_tok) - 1;
                while (end > curso_tok && (*end == ' ' || *end == '\t'))
                    *end-- = '\0';
            }

            if (nome && nusp_str && curso_tok)
            {
                Node *novo_no = (Node *)malloc(sizeof(Node));
                if (!novo_no)
                    continue;

                // *** CORREÇÃO APLICADA AQUI ***
                // Usar strdup para alocar memória separada para cada string.
                novo_no->novo.nome = strdup(nome);
                novo_no->novo.nusp = atoi(nusp_str);
                novo_no->novo.curso = strdup(curso_tok);
                novo_no->prox = NULL;

                if (!novo_no->novo.nome || !novo_no->novo.curso)
                {
                    free(novo_no->novo.nome);
                    free(novo_no->novo.curso);
                    free(novo_no);
                    continue;
                }

                if (tabela->tabela[indice] == NULL)
                {
                    tabela->tabela[indice] = novo_no;
                }
                else
                {
                    cauda->prox = novo_no;
                }
                cauda = novo_no;
            }
            aluno_tok = strtok_r(NULL, ",", &saveptr_aluno);
        }
    }

    fclose(arquivo);
    return tabela;
}

// Busca um aluno pelo nome na tabela. Retorna um ponteiro constante se encontrado.
const Aluno *buscarHash(HashT *tabela, const char *nome)
{
    if (tabela == NULL || nome == NULL)
    {
        return NULL;
    }

    int indice = funcaoHash(nome, tabela->tamanho);
    Node *atual = tabela->tabela[indice];

    while (atual != NULL)
    {
        if (strcmp(atual->novo.nome, nome) == 0)
        {
            return &atual->novo;
        }
        atual = atual->prox;
    }

    return NULL;
}

// Remove um aluno da tabela, se encontrado.
int removerHash(HashT *tabela, const char *nome)
{
    if (!tabela || !nome)
    {
        return 0; // Retorna 0 em caso de falha ou parâmetros inválidos.
    }

    int indice = funcaoHash(nome, tabela->tamanho);
    Node *atual = tabela->tabela[indice];
    Node *anterior = NULL;

    while (atual != NULL)
    {
        if (strcmp(atual->novo.nome, nome) == 0)
        {
            if (anterior == NULL)
            { // O nó a ser removido é a cabeça da lista.
                tabela->tabela[indice] = atual->prox;
            }
            else
            {
                anterior->prox = atual->prox;
            }

            free(atual->novo.nome);
            free(atual->novo.curso);
            free(atual);

            return 1; // Sucesso
        }
        anterior = atual;
        atual = atual->prox;
    }

    return 0; // Não encontrado
}

// Aloca uma nova tabela hash, ajustando seu tamanho para o próximo número primo.
HashT *criarHash(int tamanho, const char *caminho)
{
    if (tamanho <= 0 || !caminho)
    {
        return NULL;
    }

    int tamanho_primo = tamanho;
    int eh_primo = 0;
    while (!eh_primo)
    {
        eh_primo = 1;
        // Validação de primalidade (simples, mas funcional para o escopo).
        for (int i = 2; i * i <= tamanho_primo; i++)
        {
            if (tamanho_primo % i == 0)
            {
                eh_primo = 0;
                tamanho_primo++;
                break;
            }
        }
    }

    HashT *nova_tabela = (HashT *)malloc(sizeof(HashT));
    if (!nova_tabela)
    {
        return NULL;
    }

    nova_tabela->tamanho = tamanho_primo;
    nova_tabela->tabela = (Node **)calloc(tamanho_primo, sizeof(Node *));

    if (!nova_tabela->tabela)
    {
        free(nova_tabela);
        return NULL;
    }

    // Cria um arquivo vazio inicial para a nova tabela.
    salvarHash(nova_tabela, caminho);

    return nova_tabela;
}

// Insere um aluno na tabela hash.
int inserirHash(HashT *h, Aluno aluno)
{
    if (!h || !aluno.nome || !aluno.curso)
    {
        return 0;
    }

    // Verifica se o aluno já existe
    if (buscarHash(h, aluno.nome) != NULL)
    {
        return 0; // Evita duplicatas
    }

    int indice = funcaoHash(aluno.nome, h->tamanho);
    Node *novo_no = (Node *)malloc(sizeof(Node));
    if (!novo_no)
    {
        return 0;
    }

    // *** CORREÇÃO APLICADA AQUI TAMBÉM ***
    novo_no->novo.nome = strdup(aluno.nome);
    novo_no->novo.nusp = aluno.nusp;
    novo_no->novo.curso = strdup(aluno.curso);
    novo_no->prox = NULL;

    if (!novo_no->novo.nome || !novo_no->novo.curso)
    {
        free(novo_no->novo.nome);
        free(novo_no->novo.curso);
        free(novo_no);
        return 0;
    }

    // Insere o novo nó no final da lista para manter a ordem.
    if (h->tabela[indice] == NULL)
    {
        h->tabela[indice] = novo_no;
    }
    else
    {
        Node *atual = h->tabela[indice];
        while (atual->prox != NULL)
        {
            atual = atual->prox;
        }
        atual->prox = novo_no;
    }

    return 1;
}

// Libera toda a memória alocada dinamicamente pela tabela hash.
void liberarHash(HashT *h)
{
    if (!h)
        return;

    for (int i = 0; i < h->tamanho; i++)
    {
        Node *atual = h->tabela[i];
        while (atual != NULL)
        {
            Node *temp = atual;
            atual = atual->prox;
            free(temp->novo.nome);
            free(temp->novo.curso);
            free(temp);
        }
    }

    free(h->tabela);
    free(h);
}