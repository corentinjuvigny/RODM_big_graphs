# README

## Info:

Feel free to use these lines as you wish. These programs load a graph in main memory as (i) a list of edges, (ii) an adjacency matrix or (iii) an adjacency list.

## To compile:

"gcc -O9 src/main.c src/adjarray.c src/fifo.c src/bfs.c src/pagerank.c src/kcore_decomposition.c"

## To execute:

"./a.out data/my_file"  

"edgelist.txt" should contain the graph: one edge on each line (two unsigned long (nodes' ID) separated by a space).  
The program will load the graph in main memory and then terminate.

## Note:
f the graph is directed (and weighted) with selfloops and you want to make it undirected unweighted without selfloops, use the following linux command line.

awk '{if ($1<$2) print $1" "$2;else if ($2<$1) print $2" "$1}' net.txt | sort -n -k1,2 -u > net2.txt

## Initial contributors

Corentin Juvigny

Pierre Mortureux

April 2020  
