#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "aluno.h"
#include "hash.h"

#define MAX_INPUT 1024  // Tamanho m�ximo para entrada do usu�rio


void processarComando(char* comando, HashT** tabela);  // Fun��o para processar comandos do usu�rio
void trimWhitespace(char* str);  // Fun��o para remover espa�os em branco de strings
void processarMultiplosAlunos(const char* acao, char* dados, HashT** tabela, const char* caminho);  // Fun��o para processar m�ltiplos alunos
void executarTestePadrao(HashT** tabela);  // Fun��o para executar o teste padr�o do sistema

int main() {
    char input[MAX_INPUT];  // Buffer para entrada do usu�rio
    HashT* tabela = NULL;   // Ponteiro para a tabela hash

    printf("Sistema de Gerenciamento de Alunos\n");
    printf("Digite 'sair' para encerrar\n");
    printf("Pressione Enter para executar teste padr�o\n\n");

    while (1) {  // Loop principal do programa
        printf("> ");  // Prompt de comando
        fgets(input, MAX_INPUT, stdin);  // L� entrada do usu�rio
        input[strcspn(input, "\n")] = '\0';  // Remove quebra de linha

        if (strcmp(input, "sair") == 0) {  // Comando para sair do programa
            if (tabela) liberarHash(tabela);  // Libera mem�ria antes de sair
            break;
        }

        processarComando(input, &tabela);  // Processa o comando digitado
    }

    return 0;
}

void trimWhitespace(char* str) {
    char* end;  // Ponteiro para o final da string
    while(isspace((unsigned char)*str)) str++;  // Avan�a sobre espa�os iniciais
    if(*str == 0) return;  // Se string for vazia, retorna
    end = str + strlen(str) - 1;  // Posiciona no �ltimo caractere
    while(end > str && isspace((unsigned char)*end)) end--;  // Retrocede sobre espa�os finais
    *(end+1) = 0;  // Adiciona terminador de string
}

void processarMultiplosAlunos(const char* acao, char* dados, HashT** tabela, const char* caminho) {
    char* alunoPtr = dados;  // Ponteiro para percorrer os dados
    char* proximaVirgula;    // Ponteiro para pr�xima v�rgula
    int count = 0;           // Contador de opera��es realizadas

    do {
        proximaVirgula = strchr(alunoPtr, ',');  // Encontra pr�xima v�rgula
        if (proximaVirgula) *proximaVirgula = '\0';  // Substitui por terminador

        trimWhitespace(alunoPtr);  // Remove espa�os em branco

        if (strcmp(acao, "inserir") == 0) {  // Opera��o de inser��o
            char* nome = strtok(alunoPtr, ":");    // Extrai nome
            char* nuspStr = strtok(NULL, ":");    // Extrai n�mero USP
            char* curso = strtok(NULL, ":");      // Extrai curso

            if (nome && nuspStr && curso) {  // Se todos os campos existirem
                Aluno a;  // Cria estrutura Aluno
                a.nome = strdup(nome);      // Aloca e copia nome
                a.nusp = atoi(nuspStr);     // Converte n�mero USP
                a.curso = strdup(curso);    // Aloca e copia curso

                if (a.nome && a.curso) {  // Se aloca��o foi bem sucedida
                    inserirHash(*tabela, a, caminho);  // Insere na tabela
                    count++;  // Incrementa contador
                }
            }
        }
        else if (strcmp(acao, "buscar") == 0) {  // Opera��o de busca
            Aluno* encontrado = buscarHash(*tabela, alunoPtr);  // Busca aluno
            if (encontrado) {  // Se encontrou
                if (count == 0) printf("--- Alunos Encontrados ---\n");  // Cabe�alho
                printf("%s:%d:%s\n", encontrado->nome, encontrado->nusp, encontrado->curso);  // Exibe dados
                count++;  // Incrementa contador
            } else {  // Se n�o encontrou
                printf("Aluno '%s' n�o encontrado.\n", alunoPtr);  // Mensagem
            }
        }
        else if (strcmp(acao, "remover") == 0) {  // Opera��o de remo��o
            if (removerHash(*tabela, alunoPtr, caminho)) {  // Remove aluno
                count++;  // Incrementa contador se removeu
            } else {  // Se n�o encontrou
                printf("Aluno '%s' n�o encontrado para remo��o.\n", alunoPtr);  // Mensagem
            }
        }

        if (proximaVirgula) {  // Se havia v�rgula
            *proximaVirgula = ',';  // Restaura v�rgula original
            alunoPtr = proximaVirgula + 1;  // Avan�a para pr�ximo aluno
        }
    } while (proximaVirgula != NULL);  // Repete at� n�o haver mais v�rgulas

    if (count > 0) {  // Se realizou alguma opera��o
        if (strcmp(acao, "inserir") == 0) {  // Mensagem de inser��o
            printf("%d alunos inseridos com sucesso. Tabela salva em '%s'.\n", count, caminho);
        }
        else if (strcmp(acao, "remover") == 0) {  // Mensagem de remo��o
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
        processarMultiplosAlunos("inserir", dadosAluno, tabela, caminhoArquivo);  // Processa inser��o
    }

    // 3. Remover dois alunos
    printf("\n3. Removendo 2 alunos...\n");
    const char* alunosRemover[] = {"Joao", "Ana"};  // Alunos a remover
    for (int i = 0; i < 2; i++) {  // Remove cada aluno
        char nomeAluno[MAX_INPUT];
        strcpy(nomeAluno, alunosRemover[i]);  // Copia nome
        processarMultiplosAlunos("remover", nomeAluno, tabela, caminhoArquivo);  // Processa remo��o
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
        executarTestePadrao(tabela);  // Executa teste padr�o
        return;
    }

    char comandoCopia[MAX_INPUT];  // C�pia do comando para manipula��o
    strcpy(comandoCopia, comando);  // Faz c�pia do comando

    char* token = strtok(comandoCopia, " ");  // Separa primeiro token (comando)
    if (!token) return;  // Se n�o h� token, retorna

    if (strcmp(token, "criar") == 0) {  // Comando para criar tabela
        char* tamanhoStr = strtok(NULL, " ");  // Obt�m tamanho
        char* caminho = strtok(NULL, " ");     // Obt�m caminho do arquivo

        if (tamanhoStr && caminho) {  // Se ambos existem
            int tamanho = atoi(tamanhoStr);  // Converte tamanho para inteiro
            if (tamanho > 0) {  // Verifica se � v�lido
                if (*tabela) liberarHash(*tabela);  // Libera tabela existente
                *tabela = criarHash(tamanho, caminho);  // Cria nova tabela
            } else {
                printf("Tamanho deve ser um n�mero positivo.\n");  // Erro
            }
        } else {
            printf("Uso: criar <tamanho> <arquivo>\n");  // Uso incorreto
        }
    }
    else if (strcmp(token, "inserir") == 0) {  // Comando para inserir
        char* caminho = strtok(NULL, " ");  // Obt�m caminho do arquivo
        char* dados = strtok(NULL, "\0");   // Obt�m dados dos alunos

        if (caminho && dados) {  // Se ambos existem
            if (!*tabela) {  // Se tabela n�o carregada
                *tabela = carregarHash(caminho);  // Carrega tabela
                if (!*tabela) {  // Se falhou ao carregar
                    printf("Erro: Tabela n�o encontrada. Crie uma tabela primeiro.\n");
                    return;
                }
            }
            processarMultiplosAlunos("inserir", dados, tabela, caminho);  // Processa inser��o
        } else {
            printf("Uso: inserir <arquivo> <dados_aluno1>,<dados_aluno2>,...\n");  // Uso incorreto
        }
    }
    else if (strcmp(token, "buscar") == 0) {  // Comando para buscar
        char* caminho = strtok(NULL, " ");  // Obt�m caminho do arquivo
        char* nomes = strtok(NULL, "\0");   // Obt�m nomes dos alunos

        if (caminho && nomes) {  // Se ambos existem
            if (!*tabela) {  // Se tabela n�o carregada
                *tabela = carregarHash(caminho);  // Carrega tabela
                if (!*tabela) {  // Se falhou ao carregar
                    printf("Erro: Tabela n�o encontrada.\n");
                    return;
                }
            }
            processarMultiplosAlunos("buscar", nomes, tabela, caminho);  // Processa busca
        } else {
            printf("Uso: buscar <arquivo> <nome1>,<nome2>,...\n");  // Uso incorreto
        }
    }
    else if (strcmp(token, "remover") == 0) {  // Comando para remover
        char* caminho = strtok(NULL, " ");  // Obt�m caminho do arquivo
        char* nomes = strtok(NULL, "\0");   // Obt�m nomes dos alunos

        if (caminho && nomes) {  // Se ambos existem
            if (!*tabela) {  // Se tabela n�o carregada
                *tabela = carregarHash(caminho);  // Carrega tabela
                if (!*tabela) {  // Se falhou ao carregar
                    printf("Erro: Tabela n�o encontrada.\n");
                    return;
                }
            }
            processarMultiplosAlunos("remover", nomes, tabela, caminho);  // Processa remo��o
        } else {
            printf("Uso: remover <arquivo> <nome1>,<nome2>,...\n");  // Uso incorreto
        }
    }
    else if (strcmp(token, "sair") == 0) {  // Comando para sair
        if (*tabela) {  // Se tabela existe
            liberarHash(*tabela);  // Libera mem�ria
            *tabela = NULL;  // Zera ponteiro
        }
    }
    else {  // Comando desconhecido
        printf("Comando desconhecido. Comandos dispon�veis:\n");  // Lista comandos
        printf("criar <tamanho> <arquivo>\n");
        printf("inserir <arquivo> <dados_aluno1>,<dados_aluno2>,...\n");
        printf("buscar <arquivo> <nome1>,<nome2>,...\n");
        printf("remover <arquivo> <nome1>,<nome2>,...\n");
        printf("teste - Executar teste padr�o\n");
        printf("sair\n");
        printf("Pressione Enter para executar teste padr�o\n");
    }
}
