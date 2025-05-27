#include "reespalhamento.h"
#include "hashing.h"

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

void overWriteFirstLine(int size, char *path, FILE **file)
{

    // Precisamos alterar no arquivo...
    FILE *fptr;

    fptr = fopen(path, "r"); // Abrindo o arquivo para escrita no final

    // Arquivo intermediário
    FILE *temporario = fopen("../storage/temporario.txt", "w");

    if (!temporario)
    {
        perror("Erro ao criar o arquivo temporário");
        fclose(fptr);
        return;
    }

    char nova_linha[20];
    snprintf(nova_linha, sizeof(nova_linha), "%d\n", size);

    // Imprimir a nova linha
    printf("%s", nova_linha);

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
    rename("../storage/temporario.txt", path);

    (*file) = fopen(path, "a+");

    return;
}

// Encontra novo índice de posição na Hash, tanto para colisões quanto para valores antigos
int reespalhamentoQuadrático(char **organizedData, int size, int place)
{
    int i = 0, busca = place;

    while (organizedData[busca])
    {
        busca = ((i * i) + busca) % size;
        i++;
    }

    return busca;
};

// Encontra novo índice de posição na Hash, quando fator de carga <= 0.7
int reespalhamentoDuplo(char **organizedData, int size, int place)
{
    int i = 0, busca = place;

    int newHashing = 1 + ((5 * place) % (size));

    while (organizedData[busca])
    {
        i++;
        busca = (place + i * newHashing) % size;
    }

    return busca;
};

// Troca de lugar o valor antigo da hashing com o novo (reespalhamento duplo)
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
                newData[index] = oldData[i];
            }
        }
    }

    free(oldData);
    *organizedData = newData;
}


int reespalhamento(char ***organizedData, int *size, int previousHashing, int takenSpace, int *newHash, char *pathFile, FILE **fptr)
{
    double factor = ((double)(takenSpace)) / ((double)(*size));

    if (factor <= 0.7)
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
        overWriteFirstLine(*size, pathFile, fptr);

        // Realocar nova tabela com os dados antigos
        updateHashing(organizedData, oldSize, *size);

        // Retorna nova posição para a chave atual
        return reespalhamentoQuadrático(*organizedData, *size, previousHashing);
    }
    else
    {
        if (!(*newHash))
        {
            *newHash = 1;
        }

        // Reespalhamento duplo
        return reespalhamentoDuplo(*organizedData, *size, previousHashing);
    }
}
