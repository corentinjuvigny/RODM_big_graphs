#include "bfs.h"

unsigned long bfs_alg(Bfs_data *data, unsigned long s, unsigned long marker)
{
   unsigned long i, u, v, diameter;
   unsigned char gone_deeper = 0;
   FIFO_t *fifo = FIFO_Create(data->adj->n);
   FIFO_Push(fifo,s);
   data->mrkTab[s] = marker;
   if (data->nbrMrkTab != NULL)
      (data->nbrMrkTab[marker-1])++;
   diameter = 0;
   while (!FIFO_IsEmpty(fifo)) {
      u = FIFO_Pop(fifo);
      gone_deeper = 0;
      for (i = data->adj->cd[u]; i < data->adj->cd[u+1]; i++) {
         v = data->adj->adj[i];
         if (data->mrkTab[v] != marker) {
            gone_deeper = 1;
            FIFO_Push(fifo,v);
            data->mrkTab[v] = marker;
            if (data->nbrMrkTab != NULL)
               (data->nbrMrkTab[marker-1])++;
         }
      }
      if (gone_deeper > 0)
         diameter++;
   }
   FIFO_Destroy(fifo);

   return diameter;
}

static char bs_not_yet_completly_explored(Bfs_data *bs, unsigned long *pos)
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

Bfs_data *connected_graphs(adjlist *adj)
{
   Bfs_data *bs = malloc(sizeof(*bs));
   unsigned long u = 0, marker = 1;
   bs->adj = adj;
   bs->mrkTab = calloc(adj->n,sizeof(*(bs->mrkTab)));
   bs->nbrMrkTab = calloc(adj->n,sizeof(*(bs->nbrMrkTab)));

   while (bs_not_yet_completly_explored(bs,&u))
      bfs_alg(bs,u,marker++);

   return bs;
}

unsigned long diameter_of_graph(adjlist *adj)
{
   unsigned long u, diameter = 0;
   Bfs_data *bs = malloc(sizeof(*bs));
   bs->adj = adj;
   bs->mrkTab = calloc(adj->n,sizeof(*bs->mrkTab));
   bs->nbrMrkTab = NULL;
   
   for (u = 0; u < bs->adj->n; u++)
      diameter = max(diameter,bfs_alg(bs,u,1));

   bfs_free(bs);

   return diameter;
}
