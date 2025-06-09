#ifndef ALUNO_H
#define ALUNO_H

typedef struct
{
    int nUSP;
    char nome[128];
    char curso[64];
    /**
     * @brief Flag to manage the state of the hash table slot.
     * 0: Occupied - The slot contains valid student data.
     * 1: Empty - The slot has never been used.
     * 2: Tombstone - The slot was previously occupied but is now deleted.
     */
    int state;
} Aluno;

#endif // ALUNO_H