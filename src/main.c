#include <stdlib.h>
#include <stdio.h>
#include <time.h>//to estimate the runing time

#include "adjarray.h"
#include "bfs.h"
#include "pagerank.h"
#include "kcore_decomposition.h"


typedef struct {
	unsigned long v;/*noeuds*/
	unsigned long d;/*degré des noeuds*/
} noeud;


int comp_noeud( const void* l1, const void* l2) {
	/*if (l1->d>=l2->d) {
		return(-1);
	}
	else {
		return(1);
	}	*/
	return((*(noeud*)l1).d-(*(noeud*)l2).d);
}

void tri(noeud* l,int n) {
	qsort(l,n,sizeof(*l),comp_noeud);
}

void placement(noeud* l,int n,unsigned long* t) {
	/*int* t=malloc(n*sizeof(int));*/
	for (int i=0;i<n;i++) {
		t[l[i].v]=i;
	}
	/*return(t);*/
}

unsigned long max2(unsigned long* t,unsigned long n) {
	unsigned long max, ind;
	max=0;
	ind=0;
	for (unsigned long i=0;i<n;i++) {
		if (t[i]>max) {
			ind=i;
			max=t[i];
		}
	}
	return(max);
}

void DAG(adjlist* g,unsigned long* t,adjlist* dg) {
	printf("%ld\n",t[0]);
	dg->n=g->n;
	dg->e=g->e;
	unsigned long* dd=calloc(g->n,sizeof(int));
	/*t=tri(l,dg->n);*/
	//dg->edges=malloc(g->e*sizeof(edge));
	unsigned long i,u,v;
	/*unsigned long de=0;*/
	printf("Pute\n");
	for (i=0;i<g->e;i++) {
		if(t[g->edges[i].s]<t[g->edges[i].t]) {
			
			dd[g->edges[i].s]++;
			//printf("egfvguyug: %ld\n",dd[g->edges[i].s]);
		}
		else {
			dd[g->edges[i].t]++;
		}
	}
	printf("yeet %ld\n",i);/*
	for (i=0;i<g->e;i++) {
		d[g->edges[i].s]++;
		d[g->edges[i].t]++;
	}*/
	printf("max e: %ld, n: %ld, e:%ld\n",max2(dd,dg->n),dg->n,dg->e);
	printf("salope\n");
	dg->cd=calloc((dg->n+1),sizeof(unsigned long));
	dg->cd[0]=0;
	for (i=1;i<dg->n+1;i++) {
		//printf("dd: %ld %ld\n",dd[i-1],i-1);
		dg->cd[i]=dg->cd[i-1]+dd[i-1];
		dd[i-1]=0;
	}
	printf("cd: %ld %ld\n",dg->cd[g->n],g->cd[g->n]);
	
	dg->adj=malloc(	dg->e*sizeof(unsigned long));
	printf("petite pute\n");
	for (i=0;i<g->e;i++) {
		u=g->edges[i].s;
		v=g->edges[i].t;
		if(t[u]<t[v]) {
			dg->adj[ dg->cd[u] + dd[u]++ ]=v;
		}
		else {
			dg->adj[ dg->cd[v] + dd[v]++ ]=u;
		}
	}
	printf("chien de la casse\n");
	free(dd);
	/*free(g->edges);*/
}


/*

unsigned long compte_triangle(adjlist* g) {
	printf("Juvisy\n");
	unsigned long* t=malloc((g->n)*sizeof(int));
	adjlist *dg=malloc(sizeof(adjlist));
	noeud* l=malloc(g->n * sizeof(noeud));
	int i,j,u,v,y,z;
	unsigned long ct=0;
	for(i=0;i<g->n;i++) {
		l[i].v=i;
		l[i].d=g->cd[i+1]-g->cd[i];
	}
	printf("Alfortville\n");
	tri(l,g->n);
	printf("Vigneux\n");
	placement(l,g->n,t);
	printf("Ris orangis\n");
	DAG( g,t,dg);
	printf("evry\n");
	printf("max e: %ld, n: %ld, e:%ld\n",max2(dg->adj,dg->e),dg->n,dg->e);
	printf("haha\n");
	printf("%ld\n",dg->adj[25000]);
	
	for(i=0;i<dg->n;i++) {
		//printf("Ourcq\n");
		for(j=dg->cd[i];j<dg->cd[i+1];j++) {
			//printf("Laumière\n");
			for(u=dg->cd[i];u<dg->cd[i+1];u++) {
				//printf("Stalingrad\n");
				if(t[(dg->adj)[u]]>t[(dg->adj)[j]]) {
					printf("Gare de l'Est\n");
					for(v=dg->cd[(dg->adj)[j]];v=dg->cd[(dg->adj)[j]+1];j++) {
						if((dg->adj)[u]==(dg->adj)[v]){
							ct=ct+1;
							break;
						}
					}
				}
			}
		}
	}
	printf("lol\n");			
	return(ct);
}
*/


unsigned long compte_triangle(adjlist* g) {
	printf("Juvisy\n");
	
	
	noeud* l=malloc(g->n * sizeof(noeud));
	unsigned long i,j,u,v,y,z;
	unsigned long ct=0;
	for(i=0;i<g->n;i++) {
		l[i].v=i;
		l[i].d=g->cd[i+1]-g->cd[i];
	}
	
	mkdirectedadjlist(g);
	adjlist* dg=g;
	
	for(i=0;i<dg->n;i++) {
		for(j=dg->cd[i];j<dg->cd[i+1];j++) {
			
			for(u=dg->cd[i];u<dg->cd[i+1];u++) {
				
				if((dg->adj)[u]>(dg->adj)[j]) {
					//printf("Gare de l'Est\n");
					for(v=dg->cd[dg->adj[j]];v<dg->cd[((dg->adj)[j])+1];v++) {
						//printf("%ld %ld\n",v,u);
						if((dg->adj)[u]==(dg->adj)[v]){
							ct=ct+1;
							break;
						}
					}
					//printf("lol\n");
				}
			}
		}
	}
	printf("mdr\n");			
	return(ct);
}

void melanger(unsigned long* tab,int nb)
{
    unsigned long i,nb2;
    nb2 = nb;
    for(i=0;i<nb;i++)
    {
        unsigned long tmp;
        unsigned long index = rand()%nb2;
        tmp = tab[index];
        tab[index] = tab[nb2-1];
        tab[nb-i-1] = tmp;
        nb2--;
    }
}



unsigned long max_lab(unsigned long i,adjlist* g,unsigned long* label) {
	int j;
	unsigned long* lab2=calloc(g->n,sizeof(unsigned long));
	for(j=g->cd[i];j=g->cd[i+1];j++) {
		lab2[label[g->adj[j]]]++;
	}
	return(max2(lab2,g->n));
}
	

unsigned long* label_propagation(adjlist* g) {
	int i,j,n,index,condition;
	n=g->n;
	unsigned long* t=malloc(n*sizeof(unsigned long));
	unsigned long* label=malloc(n*sizeof(unsigned long));	
	for (i=0;i<g->n;i++) {
		t[i]=i;
		label[i]=i;
	}
	condition=1;
	while(condition) {
		melanger(t,n);
		for (i=0;i<g->n;i++) {
			label[t[i]]=max_lab(t[i],g,label);
		}
		condition=0;
		for (i=0;i<g->n;i++) {
			if(label[i]!=max_lab(t[i],g,label)) {
				condition=0;
				break;
			}
		}
	}
	return(label);
}	
		

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
	mkadjlist(g); // generate undirected graph
	//mkdirectedadjlist(g); // generate directed graph
   
	unsigned long ct=compte_triangle(g);
	printf("triangle of g: %ld\n",ct);
	
	t2=time(NULL);

	printf("- Overall time = %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));
	
/* Exercice 1 

   printf("br of nodes : %ld, nbr of edges : %ld\n",g->n,g->e);

   unsigned long maxSizeComp, nbrComp;

   Bfs_data *bs = connected_graphs(g,&maxSizeComp,&nbrComp);

   bfs_show(bs);

   bfs_free(bs);

   unsigned long diameter = diameter_of_graph(g);

   printf("Diameter of g: %ld, nbr of components = %ld, max comp size = %ld\n",diameter,nbrComp,maxSizeComp);
*/

/* Exercice 2 */
   /*  
   double *pgr = pagerank(g,20,0.15);
   
   for (unsigned int i = 0; i < g->n; i++)
      printf("%E ",pgr[i]);
   printf("\n");

   free(pgr);
*/

#if 0
   Kcore_info kc = coreDecomposition(g);

   printf("%ld\n",kc.cost_max);

   for (unsigned int i = 0; i < g->n; i++)
      printf("%ld %ld ; ",kc.cost[i],kc.order[i]);
   printf("\n");

   free_kcore(&kc);
#endif   

   free_adjlist(g);

	return 0;
}
