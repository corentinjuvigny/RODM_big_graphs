#include "adjarray.h"

static inline unsigned long norm_vect(const adjlist *adj, const double *p)
{
   unsigned long e, res = 0;
   for (e = 0; e < adj->e; e++)
      res += p[adj->edges[e].s];
   return res;
}

void pagerank(adjlist *adj, unsigned int t, double alpha)
{
   unsigned long *d = calloc(adj->e,sizeof(unsigned long));
   double *p = malloc(adj->n*sizeof(*p));
   unsigned long e, norm;
   unsigned int i;

   for (e = 0; e < adj->e; e++) {
      d[adj->edges[e].s]++;
      p[e] = 1/adj->n;
   }

   for (i = 0; i < t; i++) {
      for (e = 0; e < adj->e; e++) {
         p[adj->edges[e].s] = d[adj->edges[e].s] > 0 ? p[adj->edges[e].s]/d[adj->edges[e].s] : p[adj->edges[e].s];
      }
      for (e = 0; e < adj->e; e++) {
         p[adj->edges[e].s] = (1 - alpha) * p[adj->edges[e].s] + alpha / adj->n;
      }
      norm = norm_vect(adj,p);
      for (e = 0; e < adj->e; e++)
         p[adj->edges[e].s] += (1 - norm) / adj->n;
   }

   free(p);
   free(d);
}
