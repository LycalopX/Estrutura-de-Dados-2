#include "reespalhamento.h"
#include "hashing.h"

// Encontra primo mais próximo ao dobro, e maior que o dobro do valor fornecido
int encontrarPrimo(int n)
{
    n = 2 * n + 1;

    int primo = 0;

    while (!primo)
    {
        for (int i = 3; i < n; i = i + 2)
        {
            if (n % i == 0)
            {
                n = n + 2;
                break;
            }
        }
        primo = n;
    }

    return primo;
}

// Apenas sobrescreve a primeira linha de um arquivo (serve para aumentar o tamanho da Hashing)
void overWriteFirstLine(int size, char *path)
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

    char nova_linha[20];
    snprintf(nova_linha, sizeof(nova_linha), "%d\n", size);

    // Escrever a nova primeira linha no arquivo temporário
    fputs(nova_linha, temporario);

    // Ler e descartar a primeira linha do original
    char buffer[10];
    fgets(buffer, 10, fptr); // ignora primeira linha

    // Copiar o resto do original para o temporário
    while (fgets(buffer, 10, fptr))
    {
        fputs(buffer, temporario);
    }

    fclose(fptr);
    fclose(temporario);

    // Substituir o arquivo original pelo temporário
    remove(path);
    rename("../temporario.txt", path);

    return;
}

// Reespalha índice de posição na Hashing, para Fc <= 0.7
int reespalhamentoQuadrático(char **organizedData, int size, int place)
{
    int i = 1;
    int busca = place;

    // Continue enquanto a posição está ocupada
    while (organizedData[busca] != NULL && organizedData[busca][0] != '\0' && organizedData[busca][0] != '\n')
    {
        busca = (place + i * i) % size;
        i++;
        if (i >= size) {
            fprintf(stderr, "Erro: tabela cheia, reespalhamento falhou.\n");
            return -1; // ou trate de outra forma
        }
    }
    return busca;
}

// Encontra novo índice de posição na Hash, quando fator de carga >= 0.7
int reespalhamentoDuplo(char **organizedData, int size, int place)
{
    int i = 0, busca = place;

    int newHashing = 1 + ((5 * place) % (size));

    while (organizedData[busca] != NULL && busca < size)
    {
        i++;
        busca = (place + i * newHashing) % size;
    }

    return busca;
};

// Expande array, e a atualiza com o reespalhamento quadrático (Fc >= 0.7)
void updateHashing(char ***organizedData, int oldSize, int newSize)
{
    char **oldData = *organizedData;
    char **newData = calloc(newSize, sizeof(char *));

    if (!newData)
    {
        fprintf(stderr, "Erro ao alocar memória para nova tabela hash.\n");
        return;
    }

    for (int i = 0; i < oldSize; i++)
    {
        if (oldData[i])
        {

            int nusp;
            if (sscanf(oldData[i], "%d;", &nusp) == 1)
            {
                int index = reespalhamentoQuadrático(newData, newSize, hashing(nusp) % newSize);

                newData[index] = strdup(oldData[i]);
            }
        }
    }

    free(oldData);
    *organizedData = newData;
}

int reespalhamento(char ***organizedData, int *size, int previousHashing, double factor, int *newHash, char *pathFile)
{

    if (factor < 0.7)
    {
        // Reespalhamento quadrático
        return reespalhamentoQuadrático(*organizedData, *size, previousHashing);
    }
    else if (factor >= 0.9)
    {

        // Expansão da tabela
        int oldSize = *size;
        *size = encontrarPrimo(*size); // Novo tamanho primo

        // Atualiza o tamanho no arquivo
        overWriteFirstLine(*size, pathFile);

        // Realocar nova tabela com os dados antigos
        updateHashing(organizedData, oldSize, *size);

        *newHash = 0;

        // Retorna nova posição para a chave atual
        return reespalhamentoQuadrático(*organizedData, *size, previousHashing);
    }
    else
    {
        if (!(*newHash))
        {
            *newHash = 1;
            updateHashing(organizedData, *size, *size);
        }

        // Reespalhamento duplo
        return reespalhamentoDuplo(*organizedData, *size, previousHashing);
    }
}