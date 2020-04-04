#include "kcore_decomposition.h"

Kcore_info coreDecomposition(adjlist* adj)
{
    unsigned long n = adj->n, i, j, d, u, v, back, *deg = malloc(adj->n*sizeof(unsigned long));
    unsigned long maxdg = 0;
    unsigned long* nodeIndex = malloc(adj->n*sizeof(unsigned long));
    int* isInGraph = malloc(adj->n*sizeof(int));
    for (u = 0; u < adj->n; u++){
        deg[u] = adj->cd[u+1]-adj->cd[u];
        if (deg[u] > maxdg) maxdg = deg[u];
    }
    NodeArray nodesOfDegree[maxdg+1];

    for (d = 0; d < maxdg+1; d++)
        nodesOfDegree[d] = newArray();

    for (u = 0; u < adj->n; u++)
        isInGraph[u] = 1;

    for (u = 0; u < adj->n; u++){
        d = deg[u];
        nodeIndex[u] = nodesOfDegree[d].size;
        addNode(&nodesOfDegree[d],u);
    }

    Kcore_info res = {NULL,NULL,0};
    res.cost = malloc(adj->n*sizeof(unsigned long));
    res.order = malloc(adj->n*sizeof(unsigned long));

    while (n > 0) {
        d = 0;
        while (nodesOfDegree[d].size == 0) d++;
        u = popNode(&nodesOfDegree[d]);
        isInGraph[u] = 0;

        if (d > res.cost_max) res.cost_max = d;
        res.cost[u] = res.cost_max;
        res.order[u] = n;

        for (i = adj->cd[u]; i < adj->cd[u+1]; i++) {
            v = adj->adj[i];
            if (isInGraph[v]) {
                d = deg[v];
                j = nodeIndex[v];
                back = getBackNode(&nodesOfDegree[d]);
                nodeIndex[back] = j;
                deleteNode(&nodesOfDegree[d],j);
                nodeIndex[v] = nodesOfDegree[d-1].size;
                addNode(&nodesOfDegree[d-1],v);
                deg[v]--;
            }
        }
        n--;
    }

    return res;
}
