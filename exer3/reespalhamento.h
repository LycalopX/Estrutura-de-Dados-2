#ifndef REESPALHAMENTO_H
#define REESPALHAMENTO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int reespalhamentoQuadrático(char **organizedData, int size, int place);

int reespalhamentoDuplo(char **organizedData, int size, int place);

int reespalhamento(char ***organizedData, int *size, int place, int takenSpace, int *newHash, char *path, FILE **fptr);

#endif