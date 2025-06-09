#ifndef BUSCAR_H
#define BUSCAR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aluno.h"

int buscarHash(int nUSP, Aluno *organizedData, int size, int takenSpace);
void buscar(int argc, char **argv);

#endif