#ifndef solve_h_INCLUDED
#define solve_h_INCLUDED

struct peso
{
    int ordem;
    int kg;
};

struct pino
{

    // Lista de discos nela
    struct peso *discos;

    // Sequência de pinos ordenados (todos começam com 0)
    int streak;
    // Quantidade de discos nela
    int length;
};

void solve(struct peso *vector, int count); // Function prototype, its declaration

void printPino(struct pino x);

void inicializePinos(int count, struct pino *pino1, struct pino *pino2, struct pino *pino3);

void move(struct pino *pinos, int prevMoved, int heaviest, int *pesoMovimentado);

#endif