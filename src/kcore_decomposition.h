#ifndef __KCOR_DECOMP_H__
#define __KCOR_DECOMP_H__

#include "fifo.h"
#include "adjarray.h"

typedef struct {
   unsigned long *cost;
   unsigned long *order;
   unsigned long cost_max;
} Kcore_info;

Kcore_info coreDecomposition(adjlist* adj);

static inline void free_kcore(Kcore_info *kc)
{
   free(kc->cost);
   free(kc->order);
}

#endif
