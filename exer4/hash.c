#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"       //  Definições da tabela hash
#include "aluno.h"      // Struct Aluno

    unsigned int rotacionar13Bits(unsigned int valor) { // Função auxiliar local: Rotação de 13 bits à esquerda
        const int BITS_INT = 32; // Assumindo int de 32 bits
        return (valor << 13) | (valor >> (BITS_INT - 13));
    }

    int funcaoHash(const char* nome, int tamanhoTabela) { // Função hash principal
        if (nome == NULL || tamanhoTabela <= 0) {
            return -1; // Tratamento de erro
        }

        unsigned int h1 = 0; // Assume 0 como valor inicial

        for (int i = 0; nome[i] != '\0'; i++) { // Laço de repetição para cada caracter do nome
            h1 += (unsigned char)nome[i] << (i % 8); //COnversão dos caracteres e deslocamento inicial de bits
        }

        h1 = rotacionar13Bits(h1); // Deslocamento de bits do valor total

        return h1 % tamanhoTabela; // Compressão na tabela
    }

    void salvarHash(HashT* h, const char* caminho) {  // Função auxiliar para salvar as atualizações da tabela
        FILE* arquivo = fopen(caminho, "w");
        if (!arquivo) {
            printf("Erro ao abrir arquivo para salvar.\n"); // Tratamento de erro
            return;
        }

        for (int i = 0; i < h->tamanho; i++) {
            fprintf(arquivo, "%d: ", i); // Escreve o índice para manter um padrão na saída
            Node* atual = h->tabela[i];
            while (atual != NULL) {
                fprintf(arquivo, "%s:%d:%s", atual->novo.nome, atual->novo.nusp, atual->novo.curso); // Formato para saída Nome:Nusp:Curso
                atual = atual->prox;
                if (atual != NULL) fprintf(arquivo, ", "); // Delimitador entre alunos ","
            }
            fprintf(arquivo, "\n"); // Nova linha para o próximo índice
        }
        fclose(arquivo);
    }

 HashT* carregarHash(const char* caminhoArquivo) { // Função que garante o uso da hash atualizada a partir do arquivo txt
    FILE* arquivo = fopen(caminhoArquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir arquivo para leitura.\n"); // Tratamento de erro inicial
        return NULL;
    }

    int tamanho = 0;
    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo)) { // Contagem das linhas para determinar o tamanho
        tamanho++;
    }
    rewind(arquivo);

    HashT* tabela = (HashT*)malloc(sizeof(HashT)); // Cria tabela vazia SEM salvar (usando função interna)
    tabela->tamanho = tamanho;
    tabela->tabela = (Node**)calloc(tamanho, sizeof(Node*));

    while (fgets(linha, sizeof(linha), arquivo)) { // Processa cada linha do arquivo
        char* token = strtok(linha, ":"); // Extrai o índice considerando o padrão adotado para o arquivo
        if (!token) continue;
        int indice = atoi(token);
        char* alunos = strtok(NULL, "\n"); // Processa os alunos nesta linha
        if (!alunos) continue;
        char* aluno = strtok(alunos, ",");
        while (aluno) {

            while (*aluno == ' ') aluno++; // Remove espaços iniciais
            char* nome = strtok(aluno, ":"); // Extrai os campos separados por :
            char* nusp = strtok(NULL, ":");
            char* curso = strtok(NULL, ":");

            if (nome && nusp && curso) {
                // Cria e insere o aluno diretamente
                Node* novo = (Node*)malloc(sizeof(Node));
                novo->novo.nome = strdup(nome);
                novo->novo.nusp = atoi(nusp);
                novo->novo.curso = strdup(curso);
                novo->prox = tabela->tabela[indice];
                tabela->tabela[indice] = novo;
            }

            aluno = strtok(NULL, ",");
        }
    }

    fclose(arquivo); // Fecha o arquivo para garantir a atualização da memória
    return tabela;
}
Aluno* buscarHash(HashT* tabela, const char* nome) { //Funçaõ de busca, podendo ser indivdual ou de mais de um aluno
    if (tabela == NULL || nome == NULL) {
        return NULL; // Tratamento de erro
    }

    int indice = funcaoHash(nome, tabela->tamanho); // Cálculo do índice usando função auxliar
    Node* atual = tabela->tabela[indice];

    while (atual != NULL) {                        // Percorre a lista encadeade, haja vista que com o índice é possível encontrar o primeiro nó
        if (strcmp(atual->novo.nome, nome) == 0) {
            Aluno* copia = malloc(sizeof(Aluno));  // Faz uma cópia do aluno encontrado
            copia->nome = strdup(atual->novo.nome);
            copia->nusp = atual->novo.nusp;
            copia->curso = strdup(atual->novo.curso);
            return copia;   // Retorna a cópia alocada na memória
        }
        atual = atual->prox; // Avança para o próximo nó da lista encadeade
    }

    return NULL; // Não encontrado
}

int removerHash(HashT* tabela, const char* nome, const char* caminhoArquivo) { // Função para remover aluno, considerando a lista encadeada
    if (!tabela || !nome || !caminhoArquivo) {
        printf("Erro: Parametros invalidos para remocao.\n"); // Tratamento de erro inicial
        return 0;
    }

    int indice = funcaoHash(nome, tabela->tamanho); // Cálculo do índice usando função auxiliar
    Node* atual = tabela->tabela[indice];           // Ponteiros para lista encadeada, garantindo a remoção de apenas o aluno indicado e não do nó todo
    Node* anterior = NULL;
    int removido = 0;                               // Flag

    while (atual != NULL) {
        if (strcmp(atual->novo.nome, nome) == 0) {
            // Encontrou o aluno a ser removido, remove o nó
            if (anterior == NULL) {
                // Caso 1: Remoção do primeiro nó
                tabela->tabela[indice] = atual->prox;
            } else {
                // Caso 2: Remoção de nó no meio/fim
                anterior->prox = atual->prox;
            }

            // Libera a memória do nó removido
            free(atual->novo.nome);
            free(atual->novo.curso);
            free(atual);
            removido = 1;   // Flag para aluno removido
            break;          // Define a saída do loop
        }
        anterior = atual;
        atual = atual->prox;
    }

    if (removido) {
        salvarHash(tabela, caminhoArquivo);  // Salva a tabela após o aluno ser encontrado
    }

    return removido;
}



HashT* criarHash(int tamanho, const char* caminho) {  // Função para inicializar a tabela
    if (tamanho <= 0 || !caminho) {
        printf("Erro: Parametros invalidos.\n"); // Tratamento de erro inical
        return NULL;
    }

    int tamanho_primo = tamanho;
    int eh_primo = 0;

    while (!eh_primo) {  // Loop para verificar primo mais próximo e ajuste da tabela
        eh_primo = 1;
        for (int i = 2; i <= tamanho_primo / 2; i++) {
            if (tamanho_primo % i == 0) {
                eh_primo = 0;
                break;
            }
        }
        if (!eh_primo) tamanho_primo++;
    }

    HashT* nova_tabela = (HashT*)malloc(sizeof(HashT));  // Alocação da tabela em memória
    if (!nova_tabela) {
        printf("Erro: Falha na alocação da tabela hash.\n");
        return NULL;
    }

    nova_tabela->tamanho = tamanho_primo;
    nova_tabela->tabela = (Node**)calloc(tamanho_primo, sizeof(Node*));  // Alocação feita conforme struct HashT e Node

    if (!nova_tabela->tabela) {
        printf("Erro: Falha na alocação do array de nós.\n");
        free(nova_tabela);
        return NULL;
    }

    nova_tabela->caminho_arquivo = strdup(caminho);  // Guarda o caminho
    salvarHash(nova_tabela, caminho);

    printf("Tabela hash criada e salva em '%s' (tamanho: %d).\n", caminho, tamanho_primo); // Mensagem de sucesso e tabela inicializada
    return nova_tabela;
}

int inserirHash(HashT* h, Aluno aluno, const char* caminhoArquivo) {
    if (!h || !aluno.nome || !aluno.curso || !caminhoArquivo) {
        printf("Erro: Parametros invalidos para insercao.\n");  // Tratamento de erro incial
        return 0;
    }

    int indice = funcaoHash(aluno.nome, h->tamanho);  // Cálculo do íncide utilizando função auxiliar
    Node* novo_no = (Node*)malloc(sizeof(Node));      // Alocação de memória
    if (!novo_no) {
        printf("Erro: Falha na alocacao de memoria.\n");
        return 0;
    }

    novo_no->novo.nome = strdup(aluno.nome); // Cópia dos dados
    novo_no->novo.nusp = aluno.nusp;
    novo_no->novo.curso = strdup(aluno.curso);
    novo_no->prox = NULL;
    novo_no->removido = 0;  // Novo campo: marcação de nó removido

    // Caso 1: Posição vazia, considerandando a situação de lista encadeada
    if (h->tabela[indice] == NULL) {
        h->tabela[indice] = novo_no;
    }
    // Caso 2: Procura por espaço vago (nó marcado como removido)
    // Evita inserção fora de ordem
    else {
        Node* atual = h->tabela[indice];
        Node* anterior = NULL;
        int inserido = 0;

        while (atual != NULL) {
            if (atual->removido) {
                // Reutiliza espaço vago
                free(atual->novo.nome);
                free(atual->novo.curso);
                *atual = *novo_no;  // Copia os dados
                free(novo_no);
                inserido = 1;
                break;
            }
            anterior = atual;
            atual = atual->prox;
        }

        // Caso 3: Sem espaços vagos, insere no final
        if (!inserido) {
            anterior->prox = novo_no;
        }
    }

    salvarHash(h, caminhoArquivo); // Salva a tabela hash após inserção bem sucedida
    printf("Aluno '%s' inserido com sucesso no indice %d. Tabela salva em '%s'.\n",
           aluno.nome, indice, caminhoArquivo);
    return 1;
}

void liberarHash(HashT* h) {
    if (!h) return;

    // Libera todos os nós da tabela (toda memória alocada)
    for (int i = 0; i < h->tamanho; i++) {
        Node* atual = h->tabela[i];
        while (atual != NULL) {
            Node* temp = atual;
            atual = atual->prox;
            free(temp->novo.nome);
            free(temp->novo.curso);
            free(temp);
        }
    }

    // Libera o array de ponteiros e a estrutura principal
    free(h->tabela);
    free(h);
}
