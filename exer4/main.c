#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "aluno.h"
#include "hash.h"

#define MAX_INPUT 1024  // Tamanho máximo para entrada do usuário


void processarComando(char* comando, HashT** tabela);  // Função para processar comandos do usuário
void trimWhitespace(char* str);  // Função para remover espaços em branco de strings
void processarMultiplosAlunos(const char* acao, char* dados, HashT** tabela, const char* caminho);  // Função para processar múltiplos alunos
void executarTestePadrao(HashT** tabela);  // Função para executar o teste padrão do sistema

int main() {
    char input[MAX_INPUT];  // Buffer para entrada do usuário
    HashT* tabela = NULL;   // Ponteiro para a tabela hash

    printf("Sistema de Gerenciamento de Alunos\n");
    printf("Digite 'sair' para encerrar\n");
    printf("Pressione Enter para executar teste padrão\n\n");

    while (1) {  // Loop principal do programa
        printf("> ");  // Prompt de comando
        fgets(input, MAX_INPUT, stdin);  // Lê entrada do usuário
        input[strcspn(input, "\n")] = '\0';  // Remove quebra de linha

        if (strcmp(input, "sair") == 0) {  // Comando para sair do programa
            if (tabela) liberarHash(tabela);  // Libera memória antes de sair
            break;
        }

        processarComando(input, &tabela);  // Processa o comando digitado
    }

    return 0;
}

void trimWhitespace(char* str) {
    char* end;  // Ponteiro para o final da string
    while(isspace((unsigned char)*str)) str++;  // Avança sobre espaços iniciais
    if(*str == 0) return;  // Se string for vazia, retorna
    end = str + strlen(str) - 1;  // Posiciona no último caractere
    while(end > str && isspace((unsigned char)*end)) end--;  // Retrocede sobre espaços finais
    *(end+1) = 0;  // Adiciona terminador de string
}

void processarMultiplosAlunos(const char* acao, char* dados, HashT** tabela, const char* caminho) {
    char* alunoPtr = dados;  // Ponteiro para percorrer os dados
    char* proximaVirgula;    // Ponteiro para próxima vírgula
    int count = 0;           // Contador de operações realizadas

    do {
        proximaVirgula = strchr(alunoPtr, ',');  // Encontra próxima vírgula
        if (proximaVirgula) *proximaVirgula = '\0';  // Substitui por terminador

        trimWhitespace(alunoPtr);  // Remove espaços em branco

        if (strcmp(acao, "inserir") == 0) {  // Operação de inserção
            char* nome = strtok(alunoPtr, ":");    // Extrai nome
            char* nuspStr = strtok(NULL, ":");    // Extrai número USP
            char* curso = strtok(NULL, ":");      // Extrai curso

            if (nome && nuspStr && curso) {  // Se todos os campos existirem
                Aluno a;  // Cria estrutura Aluno
                a.nome = strdup(nome);      // Aloca e copia nome
                a.nusp = atoi(nuspStr);     // Converte número USP
                a.curso = strdup(curso);    // Aloca e copia curso

                if (a.nome && a.curso) {  // Se alocação foi bem sucedida
                    inserirHash(*tabela, a, caminho);  // Insere na tabela
                    count++;  // Incrementa contador
                }
            }
        }
        else if (strcmp(acao, "buscar") == 0) {  // Operação de busca
            Aluno* encontrado = buscarHash(*tabela, alunoPtr);  // Busca aluno
            if (encontrado) {  // Se encontrou
                if (count == 0) printf("--- Alunos Encontrados ---\n");  // Cabeçalho
                printf("%s:%d:%s\n", encontrado->nome, encontrado->nusp, encontrado->curso);  // Exibe dados
                count++;  // Incrementa contador
            } else {  // Se não encontrou
                printf("Aluno '%s' não encontrado.\n", alunoPtr);  // Mensagem
            }
        }
        else if (strcmp(acao, "remover") == 0) {  // Operação de remoção
            if (removerHash(*tabela, alunoPtr, caminho)) {  // Remove aluno
                count++;  // Incrementa contador se removeu
            } else {  // Se não encontrou
                printf("Aluno '%s' não encontrado para remoção.\n", alunoPtr);  // Mensagem
            }
        }

        if (proximaVirgula) {  // Se havia vírgula
            *proximaVirgula = ',';  // Restaura vírgula original
            alunoPtr = proximaVirgula + 1;  // Avança para próximo aluno
        }
    } while (proximaVirgula != NULL);  // Repete até não haver mais vírgulas

    if (count > 0) {  // Se realizou alguma operação
        if (strcmp(acao, "inserir") == 0) {  // Mensagem de inserção
            printf("%d alunos inseridos com sucesso. Tabela salva em '%s'.\n", count, caminho);
        }
        else if (strcmp(acao, "remover") == 0) {  // Mensagem de remoção
            printf("%d alunos removidos com sucesso. Tabela salva em '%s'.\n", count, caminho);
        }
    }
}

void executarTestePadrao(HashT** tabela) {
    const char* caminhoArquivo = "hash_teste.txt";  // Arquivo para salvar tabela

    // 1. Criar tabela hash com tamanho 11
    if (*tabela) liberarHash(*tabela);  // Libera tabela existente
    *tabela = criarHash(11, caminhoArquivo);  // Cria nova tabela
    if (!*tabela) {  // Verifica se criou com sucesso
        printf("Erro ao criar tabela hash.\n");
        return;
    }

    // 2. Inserir cinco alunos
    printf("\n2. Inserindo 5 alunos...\n");
    const char* alunosInserir[] = {  // Dados dos alunos
        "Joao:1234567:Engenharia",
        "Maria:7654321:Medicina",
        "Carlos:9876543:Direito",
        "Ana:1928374:Arquitetura",
        "Pedro:9182736:Administracao"
    };

    for (int i = 0; i < 5; i++) {  // Insere cada aluno
        char dadosAluno[MAX_INPUT];
        strcpy(dadosAluno, alunosInserir[i]);  // Copia dados
        processarMultiplosAlunos("inserir", dadosAluno, tabela, caminhoArquivo);  // Processa inserção
    }

    // 3. Remover dois alunos
    printf("\n3. Removendo 2 alunos...\n");
    const char* alunosRemover[] = {"Joao", "Ana"};  // Alunos a remover
    for (int i = 0; i < 2; i++) {  // Remove cada aluno
        char nomeAluno[MAX_INPUT];
        strcpy(nomeAluno, alunosRemover[i]);  // Copia nome
        processarMultiplosAlunos("remover", nomeAluno, tabela, caminhoArquivo);  // Processa remoção
    }

    // 4. Buscar alunos (2 existentes e 1 inexistente)
    printf("\n4. Buscando alunos...\n");
    const char* alunosBuscar[] = {"Maria", "Pedro", "Tiago"};  // Alunos a buscar
    for (int i = 0; i < 3; i++) {  // Busca cada aluno
        char nomeBusca[MAX_INPUT];
        strcpy(nomeBusca, alunosBuscar[i]);  // Copia nome
        processarMultiplosAlunos("buscar", nomeBusca, tabela, caminhoArquivo);  // Processa busca
    }
}

void processarComando(char* comando, HashT** tabela) {
    // Verifica se foi pressionado apenas Enter (comando vazio)
    if (strlen(comando) == 0) {
        executarTestePadrao(tabela);  // Executa teste padrão
        return;
    }

    char comandoCopia[MAX_INPUT];  // Cópia do comando para manipulação
    strcpy(comandoCopia, comando);  // Faz cópia do comando

    char* token = strtok(comandoCopia, " ");  // Separa primeiro token (comando)
    if (!token) return;  // Se não há token, retorna

    if (strcmp(token, "criar") == 0) {  // Comando para criar tabela
        char* tamanhoStr = strtok(NULL, " ");  // Obtém tamanho
        char* caminho = strtok(NULL, " ");     // Obtém caminho do arquivo

        if (tamanhoStr && caminho) {  // Se ambos existem
            int tamanho = atoi(tamanhoStr);  // Converte tamanho para inteiro
            if (tamanho > 0) {  // Verifica se é válido
                if (*tabela) liberarHash(*tabela);  // Libera tabela existente
                *tabela = criarHash(tamanho, caminho);  // Cria nova tabela
            } else {
                printf("Tamanho deve ser um número positivo.\n");  // Erro
            }
        } else {
            printf("Uso: criar <tamanho> <arquivo>\n");  // Uso incorreto
        }
    }
    else if (strcmp(token, "inserir") == 0) {  // Comando para inserir
        char* caminho = strtok(NULL, " ");  // Obtém caminho do arquivo
        char* dados = strtok(NULL, "\0");   // Obtém dados dos alunos

        if (caminho && dados) {  // Se ambos existem
            if (!*tabela) {  // Se tabela não carregada
                *tabela = carregarHash(caminho);  // Carrega tabela
                if (!*tabela) {  // Se falhou ao carregar
                    printf("Erro: Tabela não encontrada. Crie uma tabela primeiro.\n");
                    return;
                }
            }
            processarMultiplosAlunos("inserir", dados, tabela, caminho);  // Processa inserção
        } else {
            printf("Uso: inserir <arquivo> <dados_aluno1>,<dados_aluno2>,...\n");  // Uso incorreto
        }
    }
    else if (strcmp(token, "buscar") == 0) {  // Comando para buscar
        char* caminho = strtok(NULL, " ");  // Obtém caminho do arquivo
        char* nomes = strtok(NULL, "\0");   // Obtém nomes dos alunos

        if (caminho && nomes) {  // Se ambos existem
            if (!*tabela) {  // Se tabela não carregada
                *tabela = carregarHash(caminho);  // Carrega tabela
                if (!*tabela) {  // Se falhou ao carregar
                    printf("Erro: Tabela não encontrada.\n");
                    return;
                }
            }
            processarMultiplosAlunos("buscar", nomes, tabela, caminho);  // Processa busca
        } else {
            printf("Uso: buscar <arquivo> <nome1>,<nome2>,...\n");  // Uso incorreto
        }
    }
    else if (strcmp(token, "remover") == 0) {  // Comando para remover
        char* caminho = strtok(NULL, " ");  // Obtém caminho do arquivo
        char* nomes = strtok(NULL, "\0");   // Obtém nomes dos alunos

        if (caminho && nomes) {  // Se ambos existem
            if (!*tabela) {  // Se tabela não carregada
                *tabela = carregarHash(caminho);  // Carrega tabela
                if (!*tabela) {  // Se falhou ao carregar
                    printf("Erro: Tabela não encontrada.\n");
                    return;
                }
            }
            processarMultiplosAlunos("remover", nomes, tabela, caminho);  // Processa remoção
        } else {
            printf("Uso: remover <arquivo> <nome1>,<nome2>,...\n");  // Uso incorreto
        }
    }
    else if (strcmp(token, "sair") == 0) {  // Comando para sair
        if (*tabela) {  // Se tabela existe
            liberarHash(*tabela);  // Libera memória
            *tabela = NULL;  // Zera ponteiro
        }
    }
    else {  // Comando desconhecido
        printf("Comando desconhecido. Comandos disponíveis:\n");  // Lista comandos
        printf("criar <tamanho> <arquivo>\n");
        printf("inserir <arquivo> <dados_aluno1>,<dados_aluno2>,...\n");
        printf("buscar <arquivo> <nome1>,<nome2>,...\n");
        printf("remover <arquivo> <nome1>,<nome2>,...\n");
        printf("teste - Executar teste padrão\n");
        printf("sair\n");
        printf("Pressione Enter para executar teste padrão\n");
    }
}
