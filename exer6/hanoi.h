#ifndef solve_h_INCLUDED
#define solve_h_INCLUDED

struct peso
{
    int ordem;
    int kg;
};

struct pino
{
    struct peso *discos;
    int length;
};

void hanoi(struct pino *pinos, int n, char from, char to, char support, int *movedWeight, int *numberOfMoves); // Function prototype, its declaration

void setUp(int *weights, int count);

void allocateDisks(struct pino **pinos, int count, int *weights);

#endif