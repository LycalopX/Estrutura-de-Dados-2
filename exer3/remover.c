#include "buscar.h"
#include "readHashing.h"

// Atualiza o arquivo original com os dados modificados da tabela hash
void updateFile(char **organizedData, char *path)
{
    FILE *fptr = fopen(path, "r");
    FILE *temporario = fopen("../temporario.txt", "w");

    if (!temporario)
    {
        perror("Erro ao criar o arquivo temporário");
        fclose(fptr);
        return;
    }

    // Copia a primeira linha (tamanho da tabela)
    char buffer[10];
    fgets(buffer, 10, fptr);
    fputs(buffer, temporario);

    // Escreve os dados atualizados no arquivo temporário
    for (int i = 0; organizedData[i] != NULL; i++)
    {
        fputs(organizedData[i], temporario);
        fputs("\n", temporario);
    }

    fclose(fptr);
    fclose(temporario);

    // Substitui o arquivo original pelo novo com os dados atualizados
    remove(path);
    rename("../temporario.txt", path);
}

// Remove os alunos indicados pelos NUSPs passados como argumento
void remover(int argc, char **argv)
{
    char *path = argv[2];
    char *nUSPs = argv[3];
    char *token = strtok(nUSPs, ",");

    char pathFile[64], **organizedData;
    int size, takenSpace = 0, nUSP, index;

    snprintf(pathFile, sizeof(pathFile), "../%s.txt", path); // Caminho completo do arquivo

    // Lê tabela atual para a memória
    readHashing(&organizedData, pathFile, &size, &takenSpace);

    // Para cada NUSP passado, busca e marca com lápide
    while (token)
    {
        nUSP = atoi(token);
        index = buscarHash(nUSP, organizedData, size);

        if (index >= 0)
        {
            printf("Aluno NUSP %d removido\n", nUSP);

            // Marca a posição com uma lápide '+'
            free(organizedData[index]);
            organizedData[index] = (char *)malloc(256 * sizeof(char));
            organizedData[index][0] = '+';
        }

        token = strtok(NULL, ",");
    }

    // Salva a tabela modificada no arquivo
    updateFile(organizedData, pathFile);

    printf("Usuários solicitados removidos.\n\n");
}
