#ifndef __BFS_H__
#define __BFS_H__

#include "fifo.h"
#include "adjarray.h"

#define Inline static inline
#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

typedef struct _Bfs_data Bfs_data;
typedef const Bfs_data CBfs_data;
struct _Bfs_data {
   adjlist *adj;
   unsigned long *mrkTab;
   unsigned long *nbrMrkTab;
};

extern unsigned long bfs_alg(Bfs_data *data, 
                             unsigned long *farthest,
                             unsigned long *nbrElementComp,
                             unsigned long s,
                             unsigned long marker);

extern Bfs_data *connected_graphs(adjlist *adj, unsigned long *maxSizeComp, unsigned long *nbrComp);

extern unsigned long diameter_of_graph(adjlist *adj);

Inline void bfs_free(Bfs_data *bs)
{
   if (bs->nbrMrkTab) free(bs->nbrMrkTab);
   if (bs->mrkTab) free(bs->mrkTab);
   free(bs);
}

Inline void bfs_show(Bfs_data *bs)
{
   unsigned long u;
   for (u = 0; u < bs->adj->n; u++) {
      printf("%ld ",bs->mrkTab[u]);
   }
   printf("\n\n");
   for (u = 0; u < bs->adj->n; u++) {
      if (bs->nbrMrkTab[u] == 0) break;
      printf("(%ld : %ld) ",u,bs->nbrMrkTab[u]);
   }
   printf("\n");
}

#endif
