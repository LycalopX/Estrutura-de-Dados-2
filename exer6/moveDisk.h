#include "hanoi.h"

#ifndef moveDisk_h_INCLUDED
#define moveDisk_h_INCLUDED

void moveDisk(struct pino *pinos, int n1, int n2, int *movedWeight);
static inline void swapDisk(struct peso *disk1, struct peso *disk2);

#endif