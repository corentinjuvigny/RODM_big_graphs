#ifndef __BFS_H__
#define __BFS_H__

#include "fifo.h"
#include "adjarray.h"

typedef struct _Bfs_data Bfs_data;
typedef const Bfs_data CBfs_data;
struct _Bfs_data {
   adjlist *adj;
   unsigned long *mrkTab;
};

void bfs_alg(Bfs_data *data, unsigned long s, unsigned long marker);

unsigned long *connected_graphs(adjlist *adj);

#endif
