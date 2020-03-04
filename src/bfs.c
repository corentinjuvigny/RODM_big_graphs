#include "bfs.h"

void bfs_alg(Bfs_data *data, unsigned long s, unsigned long marker)
{
   unsigned long i;
   Fifo *fifo = fifo_alloc(data->adj->n * sizeof(data->adj->n));
   fifo_put(fifo,&s,sizeof(s));
   while (fifo_len(fifo) > 0) {
      unsigned long u;
      fifo_get(fifo,&u,sizeof(u));
      for (i = data->adj->cd[u]; i < data->adj->cd[u]+1; i++) {
         unsigned long v = data->adj->adj[i];
         if (data->mrkTab[i] != marker) {
            fifo_put(fifo,&v,sizeof(v));
            data->mrkTab[i] = marker;
         }
      }
   }
}

unsigned long *connected_graphs(adjlist *adj)
{

}
