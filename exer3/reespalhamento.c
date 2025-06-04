#include "reespalhamento.h"
#include "hashing.h"

// Encontra o próximo número primo maior que o dobro de n
int encontrarPrimo(int n)
{
    n = 2 * n + 1;

    int primo = 0;

    // Testa até achar um primo
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

// Sobrescreve a primeira linha do arquivo com o novo tamanho da tabela
void overWriteFirstLine(int size, char *path)
{
    FILE *fptr = fopen(path, "r");
    FILE *temporario = fopen("../temporario.txt", "w");

    if (!temporario)
    {
        perror("Erro ao criar o arquivo temporário");
        fclose(fptr);
        return;
    }

    char nova_linha[20];
    snprintf(nova_linha, sizeof(nova_linha), "%d\n", size);
    fputs(nova_linha, temporario); // Escreve novo tamanho

    char buffer[10];
    fgets(buffer, 10, fptr); // Descarta linha antiga

    // Copia o resto do conteúdo
    while (fgets(buffer, 10, fptr))
    {
        fputs(buffer, temporario);
    }

    fclose(fptr);
    fclose(temporario);

    // Substitui o original pelo temporário
    remove(path);
    rename("../temporario.txt", path);
}

// Tenta encontrar nova posição com reespalhamento quadrático
int reespalhamentoQuadrático(char **organizedData, int size, int place)
{
    int i = 1;
    int busca = place;

    // Procura posição vazia ou com lápide
    while (organizedData[busca] != NULL && organizedData[busca][0] != '\0' &&
           organizedData[busca][0] != '\n' && organizedData[busca][0] != '+')
    {
        busca = (place + i * i) % size;
        i++;
        if (i >= size)
        {
            fprintf(stderr, "Erro: tabela cheia, reespalhamento falhou.\n");
            return -1;
        }
    }
    return busca;
}

// Tenta nova posição usando reespalhamento duplo (usado com Fc >= 0.7)
int reespalhamentoDuplo(char **organizedData, int size, int place)
{
    int i = 0, busca = place;

    int newHashing = 1 + ((5 * place) % (size)); // h3(x)

    // Procura próxima posição disponível ignorando lápides
    while (organizedData[busca] != NULL && busca < size && organizedData[busca][0] != '+')
    {
        i++;
        busca = (place + i * newHashing) % size;
    }

    return busca;
}

// Realoca dados em nova tabela com tamanho maior, usando reespalhamento quadrático
void updateHashing(char ***organizedData, int oldSize, int newSize)
{
    char **oldData = *organizedData;
    char **newData = calloc(newSize, sizeof(char *));

    if (!newData)
    {
        fprintf(stderr, "Erro ao alocar memória para nova tabela hash.\n");
        return;
    }

    // Reinsere cada entrada na nova tabela
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

// Decide o tipo de reespalhamento com base no fator de carga e atualiza a tabela se necessário
int reespalhamento(char ***organizedData, int *size, int previousHashing, double factor, int *newHash, char *pathFile)
{
    if (factor < 0.7)
    {
        // Usa reespalhamento quadrático se ainda há bastante espaço
        return reespalhamentoQuadrático(*organizedData, *size, previousHashing);
    }
    else if (factor >= 0.9)
    {
        // Se a tabela estiver cheia, expande para novo tamanho primo
        int oldSize = *size;
        *size = encontrarPrimo(*size);

        overWriteFirstLine(*size, pathFile);
        updateHashing(organizedData, oldSize, *size);
        *newHash = 0;

        return reespalhamentoQuadrático(*organizedData, *size, previousHashing);
    }
    else
    {
        // Entre 0.7 e 0.9: ativa reespalhamento duplo
        if (!(*newHash))
        {
            *newHash = 1;
            updateHashing(organizedData, *size, *size); // apenas reorganiza
        }

        return reespalhamentoDuplo(*organizedData, *size, previousHashing);
    }
}
