#ifndef __ADJ_ARRAY_H__
#define __ADJ_ARRAY_H__

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct {
	unsigned long s;
	unsigned long t;
} edge;

//edge list structure:
typedef struct {
	unsigned long n;//number of nodes
	unsigned long e;//number of edges
	edge *edges;//list of edges
	unsigned long *cd;//cumulative degree cd[0]=0 length=n+1
	unsigned long *adj;//concatenated lists of neighbors of all nodes
} adjlist;

//reading the edgelist from file
adjlist* readedgelist(char* input);

//building the adjacency matrix
void mkadjlist(adjlist* g);

//building the directed adjency matrix
void mkdirectedadjlist(adjlist* g);

//freeing memory
void free_adjlist(adjlist *g);

#endif
