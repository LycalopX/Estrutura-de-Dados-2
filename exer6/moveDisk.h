#include "solve.h"

#ifndef moveDisk_h_INCLUDED
#define moveDisk_h_INCLUDED

void moveDisk(struct pino *origin, struct pino *destination,  int prevDest, int heaviest);
static inline void swapDisk(struct peso *disk1, struct peso *disk2);

#endif