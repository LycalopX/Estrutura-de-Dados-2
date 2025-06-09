#ifndef solver_h_INCLUDED
#define solver_h_INCLUDED

void inicializar(int n);

int resolver(int n, int col, int *rainhas, int *linUsada, int *diag1Usada, int *diag2Usada);

int verificar_solucao(int *rainhas, int n);

void rotacionar90(int *dest, int *orig, int n);

void refletir(int *dest, int *orig, int n);

int igual(int *a, int *b, int n);

#endif // solver_h_INCLUDED