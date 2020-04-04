#include "adjarray.h"

double* directedGraphProd(adjlist *adj, double *p)
{
    double* newP = malloc(adj->n*sizeof(double));
    unsigned long u = 0, j;
    
    for (u = 0; u < adj->n; u++)
        newP[u] = 0.0;

    for (u = 0; u < adj->n; u++) {
        if (adj->cd[u+1] > adj->cd[u]) {

            for (j = adj->cd[u]; j < adj->cd[u+1]; j++) {
                newP[adj->adj[j]] += p[u]/(adj->cd[u+1] - adj->cd[u]);
            }
        }
    }
    free(p);

    return newP;
}

double* pagerank(adjlist *adj, unsigned int t, double alpha)
{
   unsigned long *d = calloc(adj->n,sizeof(unsigned long));
   double *p = malloc(adj->n*sizeof(*p));
   unsigned long e;
   unsigned int i;
   double norm;

   for (e = 0; e < adj->e; e++) {
      d[adj->edges[e].s]++;
   }

   for (e = 0; e < adj->n; e++) {
      p[e] = 1.0 / (double)adj->n;
   }

   for (i = 0; i < t; i++) {
      norm = 0;
      p = directedGraphProd(adj,p);
      for (e = 0; e < adj->n; e++) {
         p[e] = (1.0 - alpha) * p[e] + alpha / (double)adj->n;
         norm += p[e];
      }
      norm = (1.0 - norm) / (double)adj->n;

      //printf("norm = %E, 1/n = %E, n = %lu\n",norm,alpha/adj->n, adj->n);
      for (e = 0; e < adj->n; e++) {
         p[e] += norm;
      }
      for (e = 0; e < adj->n; e++)
         printf("%E ",p[e]);
      printf("\n");
   }

   free(d);

   return p;
}
