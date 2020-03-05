#include "bfs.h"

void bfs_alg(Bfs_data *data, unsigned long s, unsigned long marker)
{
   unsigned long i;
   FIFO_t *fifo = FIFO_Create(data->adj->n);
   FIFO_Push(fifo,s);
   while (!FIFO_IsEmpty(fifo)) {
      unsigned long u = FIFO_Pop(fifo);
      for (i = data->adj->cd[u]; i < data->adj->cd[u+1]; i++) {
         unsigned long v = data->adj->adj[i];
         if (data->mrkTab[v] != marker) {
            fprintf(stderr,"v : %ld\n",v);
            FIFO_Push(fifo,v);
            data->mrkTab[v] = marker;
         }
      }
   }
   FIFO_Destroy(fifo);
}

static unsigned int bs_not_yet_completly_explored(Bfs_data *bs, unsigned long *pos)
{
   unsigned long u;
   for (u = *pos; u < bs->adj->n; u++) {
      if (bs->mrkTab[u] == 0) {
         *pos = u;
         return 1;
      }
   }
   return 0;
}

unsigned long *connected_graphs(adjlist *adj)
{
   Bfs_data *bs = malloc(sizeof(*bs));
   unsigned long u = 0, marker = 1, *mrkTab = calloc(adj->n,sizeof(*(bs->mrkTab)));
   bs->adj = adj;
   bs->mrkTab = mrkTab;

   while (bs_not_yet_completly_explored(bs,&u)) {
      bfs_alg(bs,u,marker);
      marker++;
   }

   free(bs);
   return mrkTab;
}
