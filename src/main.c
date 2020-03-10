#include <stdlib.h>
#include <stdio.h>
#include <time.h>//to estimate the runing time

#include "adjarray.h"
#include "bfs.h"

int main(int argc,char** argv)
{
	adjlist* g;
	time_t t1,t2;

   if (argc < 2) {
      fprintf(stderr,"Not enough arg : %d given\n",argc);
      return 1;
   }

	t1=time(NULL);

	printf("Reading edgelist from file %s\n",argv[1]);
	g=readedgelist(argv[1]);

	printf("Number of nodes: %lu\n",g->n);
	printf("Number of edges: %lu\n",g->e);

	printf("Building the adjacency list\n");
	mkadjlist(g);

	t2=time(NULL);

	printf("- Overall time = %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));

   Bfs_data *bs = connected_graphs(g);

   bfs_show(bs);

   bfs_free(bs);

   unsigned long diameter = diameter_of_graph(g);

   printf("Diameter of g: %ld\n",diameter);

   free_adjlist(g);

	return 0;
}
