#ifndef READHASHING_H
#define READHASHING_H

#include "aluno.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Usa o nome 'Aluno' do typedef para manter a consistência com o resto do projeto.
void readHashing(Aluno **organizedData, char *pathFile, int *size, int *takenSpace);

#endif