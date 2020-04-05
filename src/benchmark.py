import random as rd
import numpy as np

def generate_graph(p,q):
    n = 400
    nbrClust = 4
    edges = []
    for i in range(n):
        for j in range(i+1,n):
            r = rd.random()
            if i < 100:
                if j < 100:
                    if r < p:
                        edges.append("{} {}".format(i,j))
                else:
                    if r < q:
                        edges.append("{} {}".format(i,j))
            elif i < 200:
                if 100 <= j < 200:
                    if r < p:
                        edges.append("{} {}".format(i,j))
                else:
                    if r < q:
                        edges.append("{} {}".format(i,j))
            elif i < 300:
                if 200 <= j < 300:
                    if r < p:
                        edges.append("{} {}".format(i,j))
                else:
                    if r < q:
                        edges.append("{} {}".format(i,j))
            else:
                if 300 <= j < 400:
                    if r < p:
                        edges.append("{} {}".format(i,j))
                else:
                    if r < q:
                        edges.append("{} {}".format(i,j)) 
    return edges

def generate_file(p,q):
    name = "benchmark_graph_{}_{}.txt".format(p,q)
    g = generate_graph(p,q)
    with open(name,'w') as f:
        f.write('\n'.join(g))

generate_file(0.3,0.1)
