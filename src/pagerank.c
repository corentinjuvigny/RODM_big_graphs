#include "adjarray.h"

static double norm_vect(const adjlist *adj, const double *p)
{
   unsigned long s;
   double res = 0.f;
   for (s = 0; s < adj->n; s++)
      res += p[s];
   return res;
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
      for (e = 0; e < adj->e; e++) {
         p[adj->edges[e].s] = d[adj->edges[e].s] > 0.0 ? p[adj->edges[e].s]/d[adj->edges[e].s] : 0.0;
      }
      for (e = 0; e < adj->n; e++) {
         p[e] = (1.0 - alpha) * p[e] + alpha / (double)adj->n;
      }
      norm = norm_vect(adj,p);
      //printf("norm = %E, 1/n = %E, n = %lu\n",norm,alpha/adj->n, adj->n);
      for (e = 0; e < adj->n; e++) {
         p[e] += (1.0 - norm) / (double)adj->n;
      }
      for (e = 0; e < adj->n; e++)
         printf("%E ",p[e]);
      printf("\n");
   }

   free(d);

   return p;
}
