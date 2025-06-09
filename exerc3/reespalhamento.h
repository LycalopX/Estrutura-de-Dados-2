#ifndef REESPALHAMENTO_H
#define REESPALHAMENTO_H

#include "aluno.h" // Include the struct definition
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// All rehashing functions are updated to work with the Aluno struct array.
int reespalhamentoQuadrático(Aluno *organizedData, int size, int place);
int reespalhamentoDuplo(Aluno *organizedData, int size, int place, int nUSP);
int reespalhamento(Aluno **organizedData, int *size, int place, double factor, int *newHash, char *path, int nUSP);

#endif