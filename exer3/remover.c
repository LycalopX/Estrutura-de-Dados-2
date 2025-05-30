#include "buscar.h"
#include "readHashing.h"

void updateFile(char **organizedData, char *path)
{

    // Precisamos alterar no arquivo...
    FILE *fptr;

    fptr = fopen(path, "r"); // Abrindo o arquivo para escrita no final

    // Arquivo intermediário
    FILE *temporario = fopen("../temporario.txt", "w");

    if (!temporario)
    {
        perror("Erro ao criar o arquivo temporário");
        fclose(fptr);
        return;
    }

    // Ler e reutilizar a primeira linha do original
    char buffer[10];
    fgets(buffer, 10, fptr); // copia tamanho da tabela
    fputs(buffer, temporario);

    // Copia array com alterações feitas
    for (int i = 0; organizedData[i] != NULL; i++)
    {
        fputs(organizedData[i], temporario);
        fputs("\n", temporario);
    }

    fclose(fptr);
    fclose(temporario);

    // Substituir o arquivo original pelo temporário
    remove(path);
    rename("../temporario.txt", path);

    return;
}

void remover(int argc, char **argv)
{
    char *path = argv[2];
    char *nUSPs = argv[3];

    char *token = strtok(nUSPs, ",");

    char pathFile[64], **organizedData;
    int size, takenSpace = 0, nUSP, index;
    // 15 + tamanho atual é o tamanho máximo do nome do arquivo

    snprintf(pathFile, sizeof(pathFile), "../%s.txt", path); // Salvando na pasta storage.

    readHashing(&organizedData, pathFile, &size, &takenSpace);

    while (token)
    {
        nUSP = atoi(token);

        index = buscarHash(nUSP, organizedData, size);

        if (index > 0)
        {
            printf("Aluno NUSP %d removido\n", nUSP);
            // fazer lápide
        }

        token = strtok(NULL, ","); // Próximo número USP
    }

    updateFile(organizedData, pathFile);

    printf("Usuários solicitados removidos.\n\n");
}